/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:02:30 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/09 20:27:52 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_type 	get_outfile_type(t_data *data, int cmd, int index)
{
	t_parse *parse;
	int		i;

	parse = data->parse;
	i = 0;
	while (parse[i].type != FINISH && parse[i].cmd != cmd)
		i++;
	while (parse[i].type != FINISH && parse[i].cmd == cmd)
	{
		if (!index && (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T))
			return (parse[i].type);
		else if (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T)
			index--;
		i++;
	}
	return (FINISH);
}

int				ft_ambigous(t_data *data, int cmd, char c, int index)
{
	t_lexer *ptr;
	
	ptr = data->lexer;
	if (c == 'i')
	{
		while (ptr)
		{
			if (ptr->type == INF_CHEVRON && ptr->next->content[0] == '$')
				break ;
			ptr = ptr->next;
		}
		if (data->exec[cmd - 1].infile[index][0] == '\0')
		{
			printf("minishell: %s: ambiguous redirect\n", ptr->next->content);
			return (1);
		}
	}
	else if (c == 'o')
	{
		while (ptr)
		{
			if ((ptr->type == SUP_CHEVRON || ptr->type == D_SUP_CHEVRON) && ptr->next->content[0] == '$')
				break ;
			ptr = ptr->next;
		}
		if (data->exec[cmd - 1].outfile[index][0] == '\0')
		{
			printf("minishell: %s: ambiguous redirect\n", ptr->next->content);
			return (1);
		}
	}
	return (0);
}

int				handle_infile(t_data *data, int cmd, int i)
{
	int filein; 
	
	if (ft_ambigous(data, cmd, 'i', i))
		exit(0);
	filein = open(data->exec[cmd - 1].infile[i], O_RDONLY, 0644);
	if (filein < 0)
	{
		perror(data->exec[cmd - 1].infile[i]);
		close_pipes(data);
		exit(EXIT_FAILURE);
	}
	dup2(filein, STDIN_FILENO);
	close(data->fd[0]);
	return (1);
}

int				handle_outfile(t_data *data, int cmd, int i)
{
	int fileout;
	
	if (ft_ambigous(data, cmd, 'o', i))
		exit(0);
	if (get_outfile_type(data, cmd, i) == OUTFILE_T)
		fileout = open(data->exec[cmd - 1].outfile[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (get_outfile_type(data, cmd, i) == OUTFILE_A)
		fileout = open(data->exec[cmd - 1].outfile[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fileout < 0)
	{
		perror(data->exec[cmd - 1].outfile[i]);
		close_pipes(data);
		exit(EXIT_FAILURE);
	}
	dup2(fileout, STDOUT_FILENO);
	close(data->fd[1]);
	return (1); 
}

int				is_same_string(char *line, char *limiter)
{
	if (line[0] == '\n')
		return (0);
	if (ft_strncmp(line, limiter, ft_strlen(limiter) - 1) == 0 && ft_strlen(line) - 1 == ft_strlen(limiter))
		return (1);
	else
		return (0);
		
}

void			handle_heredoc(t_data *data, int cmd, int status)
{
	t_parse *parse;
	int		i;
	char	*line;

	if (status > 0)
		data->tmpfd = open(data->tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	parse = data->parse;
	i = 0;
	while (parse[i].type != FINISH && parse[i].cmd != cmd)
		i++;
	while (parse[i].type != FINISH && parse[i].cmd == cmd)
	{
		if (parse[i].type == LIMITER)
		{
			ft_putstr_fd("> ", 2);
			line = get_next_line(0);
			while (line && !is_same_string(line, parse[i].str))
			{
				if (data->exec[cmd - 1].heredoc == 1 && status > 0)
					write(data->tmpfd, line, ft_strlen(line));
				free(line);
				ft_putstr_fd("> ", 2);
				line = get_next_line(0);
			}
			data->exec[cmd - 1].heredoc--;
		}
		i++;
	}
	close(data->tmpfd);
	if (status > 0)
	{
		data->tmpfd = open(data->tmp, O_RDONLY, 0644);
		dup2(data->tmpfd, STDIN_FILENO);
		close(data->fd[0]);
	}
}

int				handle_fd(t_data *data, int cmd)
{
	int heredoc;
	int i;
	int test;

	heredoc = 0;

	// HANDLE INFILE && HEREDOC
	if (data->exec[cmd - 1].infile)
	{
		i = 0;
		while (data->exec[cmd - 1].infile[i])
		{
			if (islastinfile(data, data->exec[cmd - 1].infile, i, cmd))
			{
				if (data->exec[cmd - 1].heredoc > 0)
					handle_heredoc(data, cmd, 0);
				if (!handle_infile(data, cmd, i))
					return (0);
			}
			else
			{
				if (ft_ambigous(data, cmd, 'i', i))
					exit(0);
				test = open(data->exec[cmd - 1].infile[i], O_RDONLY, 0644);
				if (test < 0)
				{
					perror(data->exec[cmd - 1].infile[i]);
					return (0);
				}
				close(test);
			}
			i++;
		}
	}
	if (!islastinfile(data, data->exec[cmd - 1].infile, i - 1, cmd) && data->exec[cmd - 1].heredoc > 0)
	{
		heredoc = 1;
		handle_heredoc(data, cmd, 1);
	}
	else if (!heredoc)
	{
		// dprintf(2, "three\n");
		close(data->fd[0]);
		if (cmd > 1)
			dup2(data->oldfd, STDIN_FILENO);
	}
	
	// HANDLE OUTFILE
	if (data->exec[cmd - 1].outfile)
	{
		// dprintf(2, "four\n");
		i = 0;
		while (data->exec[cmd - 1].outfile[i])
		{
			if (islastoutfile(data->exec[cmd - 1].outfile, i))
			{
				if (!handle_outfile(data, cmd, i))
					return (0);
			}
			else
			{
				if (ft_ambigous(data, cmd, 'o', i))
					exit(0);
				if (get_outfile_type(data, cmd, i) == OUTFILE_T)
					test = open(data->exec[cmd - 1].outfile[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
				else if (get_outfile_type(data, cmd, i) == OUTFILE_A)
					test = open(data->exec[cmd - 1].outfile[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
				if (test < 0)
				{
					perror(data->exec[cmd - 1].outfile[i]);
					return (0);
				}
				close(test);
			}
			i++;
		}
	}
	else
	{
		// dprintf(2, "Five\n");
		if (cmd < data->args)
			dup2(data->fd[1], STDOUT_FILENO);
		else
			close(data->fd[1]);
	}
	return (1);
}