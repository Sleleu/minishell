/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:06:00 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/10 22:52:16 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(t_data *data)
{
	char	**cmd;

	cmd = getcmd(data, 1);
	if (!cmd)
		return (0);
	if (!ft_ultracmp(cmd[0], "cd"))
		return (1);
	else if (!ft_ultracmp(cmd[0], "export"))
		return (1);
	else if (!ft_ultracmp(cmd[0], "exit"))
		return (1);
	else if (!ft_ultracmp(cmd[0], "unset"))
		return (1);
	return (0);
}

void	exec_builtout(t_data *data)
{
	char	**cmd;

	cmd = getcmd(data, 1);
	data->exit[0] = 0;
	if (!ft_ultracmp(cmd[0], "cd"))
		data->exit[1] = ft_cd(cmd, data->env);
	else if (!ft_ultracmp(cmd[0], "export"))
		data->exit[1] = ft_export(&data, cmd);
	else if (!ft_ultracmp(cmd[0], "exit"))
		ft_exit(&data, cmd);
	else if (!ft_ultracmp(cmd[0], "unset"))
		data->exit[1] = ft_unset(&data, cmd);
}