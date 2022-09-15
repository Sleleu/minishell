/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:31:46 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/16 00:30:16 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		pipe_exist(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0')
	{
		if (line[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

t_pipe *pipe_addlast(t_pipe *pipe, char *line)
{
	t_pipe *new;
	
	new = (t_pipe *)memcenter(MALLOC, sizeof(t_pipe) * 1, NULL, "Other t_pipes");
	if (!new)
		return (NULL);
	memcenter(MALLOC, 0, line, "A line");
	new->line = line;
	new->prev = pipe;
	pipe->next = new;
	return (new);
}

t_pipe *create_pipes(char *line)
{
	char	**pipes;
	t_pipe 	*first;
	t_pipe	*pipe;
	t_pipe	*tmp;
	int		i;

	pipes = (char **)memcenter(MALLOC, 0, (void *)ft_split(line, '|'), "Split pipes");
	if (!pipes)
		return (NULL);
	pipe = (t_pipe *)memcenter(MALLOC, sizeof(t_pipe) * 1, NULL, "first t_pipe");
	if (!pipe)
		return (NULL);
	memcenter(MALLOC, 0, pipes[0], "A line");
	pipe->line = pipes[0];
	pipe->next = NULL;
	pipe->prev = NULL;
	i = 1;
	tmp = pipe;
	first = pipe;
	while (pipes[i] != 0)
	{
		pipe = pipe_addlast(tmp, pipes[i]);
		tmp = pipe;
		i++;
	}
	memcenter(MALLOC, 0, pipes[i], "Last line");
	while (pipe->prev != NULL)
		pipe = pipe->prev;
	return (first);
}