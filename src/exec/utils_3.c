/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:11:15 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 21:41:57 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	err_return(char **cmd)
{
	char	*err;
	int		i;

	if (cmd[0][0] == '\0')
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
	exit(127);
}

void	close_pipes(t_data *data)
{
	if (data->fd[0] > 0)
		close(data->fd[0]);
	if (data->fd[1] > 0)
		close(data->fd[1]);
	if (data->oldfd > 0)
		close(data->oldfd);
	if (data->tmpfd > 0)
		close(data->tmpfd);
}

void	print_double(char **db)
{
	int	i;

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

int	getargsnb(t_parse *parse)
{
	int	i;

	i = 0;
	if (!parse)
		return (0);
	while (parse[i].type != FINISH)
		i++;
	if (!i)
		return (1);
	else
		return (parse[i - 1].cmd);
}
