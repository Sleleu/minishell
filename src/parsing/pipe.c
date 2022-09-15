/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:31:46 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/15 21:06:43 by sleleu           ###   ########.fr       */
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
	
	new = memcenter(MALLOC, sizeof(t_pipe *), NULL);
	if (!new)
		return (NULL);
	new->line = line;
	new->prev = pipe;
	pipe->next = new;
	return (new);
}

t_pipe *create_pipes(char *line)
{
	char	**pipes;
	t_pipe 	*pipe;
	t_pipe	*tmp;
	int		i;

	pipes = ft_split(line, '|');
	pipe = memcenter(MALLOC, sizeof(t_pipe *), NULL);
	if (!pipe)
		return (NULL);
	pipe->line = pipes[0];
	pipe->next = NULL;
	pipe->prev = NULL;
	i = 1;
	tmp = pipe;
	while (pipes[i])
	{
		pipe = pipe_addlast(tmp, pipes[i]);
		tmp = pipe;
		i++;
	}
	while (pipe->prev != NULL)
		pipe = pipe->prev;
	return (pipe);
}