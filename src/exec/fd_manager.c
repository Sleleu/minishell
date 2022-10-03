/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:02:30 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/04 00:31:20 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_type get_outfile_type(t_data *data, int cmd)
{
	t_parse *parse;
	int		i;

	parse = data->parse;
	i = -1;
	while (parse[++i].type != FINISH)
	{
		if (parse[i].cmd == cmd && (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T))
			return (parse[i].type);
	}
	return (FINISH);
}

int ft_ambigous(t_data *data, int cmd, char c)
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
		if (data->exec[cmd - 1].infile[0] == '\0')
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
			// printf("%d\n", ptr->type);
			ptr = ptr->next;
		}
		//printf("%d\n", ptr->type);
		if (data->exec[cmd - 1].outfile[0] == '\0')
		{
			printf("minishell: %s: ambiguous redirect\n", ptr->next->content);
			return (1);
		}
	}
	return (0);
}

int		handle_infile(t_data *data, int cmd)
{
	int filein; 
	
	if (ft_ambigous(data, cmd, 'i'))
		exit(0);
	filein = open(data->exec[cmd - 1].infile, O_RDONLY, 0644);
	if (filein < 0)
	{
		perror(data->exec[cmd - 1].infile);
		close_pipes(data);
		exit(EXIT_FAILURE);
	}
	dup2(filein, STDIN_FILENO);
	close(data->fd[0]);
	return (1);
}

int		handle_outfile(t_data *data, int cmd)
{
	int fileout;
	
	if (ft_ambigous(data, cmd, 'o'))
		exit(0);
	if (get_outfile_type(data, cmd) == OUTFILE_T)
		fileout = open(data->exec[cmd - 1].outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (get_outfile_type(data, cmd) == OUTFILE_A)
		fileout = open(data->exec[cmd - 1].outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fileout < 0)
	{
		perror(data->exec[cmd - 1].outfile);
		close_pipes(data);
		exit(EXIT_FAILURE);
	}
	dup2(fileout, STDOUT_FILENO);
	close(data->fd[1]);
	return (1); 
}

void			handle_heredoc(t_data *data, int cmd, int status)
{
	t_parse *parse;
	int		i;
	char	*line;

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
			while (line && (ft_strncmp(line, parse[i].str, ft_strlen(line) - 1) != 0 || line[0] == '\n'))
			{
				if (data->exec[cmd - 1].heredoc == 1 && status == 1)
					write(data->fd[1], line, ft_strlen(line));
				free(line);
				ft_putstr_fd("> ", 2);
				line = get_next_line(0);
			}
			data->exec[cmd - 1].heredoc--;
		}
		i++;
	}
}

int		handle_fd(t_data *data, int cmd)
{
	int heredoc;

	heredoc = 0;
	
	// HANDLE INFILE && HEREDOC
	if (data->exec[cmd - 1].infile && islastinfile(data, data->exec[cmd - 1].infile, cmd))
	{
		if (data->exec[cmd - 1].heredoc > 0)
			handle_heredoc(data, cmd, 0);
		if (!handle_infile(data, cmd))
			return (0);
	}
	else if (data->exec[cmd - 1].heredoc > 0)
	{
		heredoc = 1;
		handle_heredoc(data, cmd, 1);
		close(data->fd[1]);
		dup2(data->fd[0], STDIN_FILENO);
	}
	else if (!heredoc)
	{
		close(data->fd[0]);
		if (cmd > 1)
			dup2(data->oldfd, STDIN_FILENO);
	}

	
	// HANDLE OUTFILE
	if (data->exec[cmd - 1].outfile)
	{		
		if (!handle_outfile(data, cmd))
			return (0);
	}
	else
		if (cmd < data->args)
			dup2(data->fd[1], STDOUT_FILENO);
		else
			close(data->fd[1]);
	return (1);
}
