/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:17:46 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/12 15:11:34 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_same_string(char *line, char *limiter)
{
	if (line[0] == '\n')
		return (0);
	if (!ft_strncmp(line, limiter, ft_strlen(limiter) - 1)
		&& ft_strlen(line) - 1 == ft_strlen(limiter))
		return (1);
	else
		return (0);
}

char	*parse_hd_dollar(t_data *data, char *line)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = NULL;
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1] && !is_space(line[i + 1]))
		{
			i++;
			new_line = ft_varjoin(new_line, line, data->env, &i);
		}
		else
		{
			new_line = ft_charjoin(new_line, line[i]);
			i++;
		}
	}
	return (new_line);
}

char	*handle_line(t_data *data, char *line)
{
	char	*new_line;

	new_line = NULL;
	if (check_dollar(line))
	{
		new_line = parse_hd_dollar(data, line);
	}
	else
		return (line);
	return (new_line);
}

void	heredoc_boucle(t_data *data, int i, int cmd, int status)
{
	t_parse	*parse;
	char	*line;

	g_sigstatus.heredoc = 1;
	parse = data->parse;
	if (parse[i].type == LIMITER)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(0);
		while (g_sigstatus.heredoc && line
			&& !is_same_string(handle_line(data, line), parse[i].str))
		{
			if (data->exec[cmd - 1].heredoc == 1 && status > 0)
				ft_putstr_fd(handle_line(data, line), data->tmpfd);
			free(line);
			ft_putstr_fd("> ", 2);
			line = get_next_line(0);
		}
		data->exec[cmd - 1].heredoc--;
	}
	g_sigstatus.heredoc = 0;
}

int	fd_heredoc(t_data *data, int cmd, int status)
{
	int		i;

	if (status > 0)
		data->tmpfd = open(data->tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->tmpfd < 0)
	{
		perror(data->tmp);
		return (0);
	}
	i = gotoparsecmd(data, cmd);
	while (data->parse[i].type != FINISH && data->parse[i++].cmd == cmd)
		heredoc_boucle(data, i, cmd, status);
	close(data->tmpfd);
	if (status > 0)
	{
		data->tmpfd = open(data->tmp, O_RDONLY, 0644);
		if (data->tmpfd < 0)
		{
			perror(data->tmp);
			return (0);
		}
		dup2(data->tmpfd, STDIN_FILENO);
		close(data->fd[0]);
	}
	return (1);
}
