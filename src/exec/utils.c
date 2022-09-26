/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:11:15 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/26 17:17:21 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	err_return(char **cmd)
{
	char	*err;
	int		i;

	if (!cmd)
		ft_putstr_fd("command '' not found\n", 2);
	else
	{
		err = ft_strjoin(cmd[0], ": command not found\n");
		ft_putstr_fd(err, 2);
		free(err);
		i = -1;
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
	}
	close_pipes(get_data());
	exit(EXIT_FAILURE);
}

void	close_pipes(t_data *data)
{
	if (data->fd[0] > 0)
		close(data->fd[0]);
	if (data->fd[1] > 0)
		close(data->fd[1]);
	if (data->oldfd > 0)
		close(data->oldfd);
}

void print_double(char **db)
{
	int i;

	i = -1;
	while (db[++i])
		dprintf(2, "db[%d] = %s\n", i, db[i]);
}

void	free_double(char **lol)
{
	int	i;

	i = 0;
	while (lol[i])
	{
		free(lol[i]);
		i++;
	}
	free(lol);
}

int		getargsnb(t_parse *parse)
{
	int i;

	i = 0;
	if (!parse)
		return (0);
	while (parse[i].type != FINISH)
		i++;
	return (parse[i - 1].cmd);
}