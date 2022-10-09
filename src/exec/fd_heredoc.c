/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:17:46 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/09 22:54:07 by rvrignon         ###   ########.fr       */
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

void	heredoc_boucle(t_data *data, int i, int cmd, int status)
{
	t_parse	*parse;
	char	*line;

	parse = data->parse;
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
}

void	fd_heredoc(t_data *data, int cmd, int status)
{
	t_parse	*parse;
	int		i;

	if (status > 0)
		data->tmpfd = open(data->tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	parse = data->parse;
	i = gotoparsecmd(data, cmd);
	while (parse[i].type != FINISH && parse[i].cmd == cmd)
	{
		heredoc_boucle(data, i, cmd, status);
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
