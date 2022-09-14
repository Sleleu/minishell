/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:53:31 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/14 16:56:09 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_struct(void)
{
	t_data *data;
	t_pipe *pipe;
	t_pipe *tmp;

	data = get_data();
	pipe = data->pipes;
	if (!pipe)
		return ;
	while (pipe->next)
	{
		tmp = pipe;
		pipe = pipe->next;
		free(tmp);
	}
	free(pipe);
}

void	free_double(char **test)
{
	int i;

	i = 0;
	while (test[i])
	{
		free(test[i]);
		i++;
	}
	free(test[i]);
	free(test);
}