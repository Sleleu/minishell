/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:07:13 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 02:32:08 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	islastfile(t_files *file, int i)
{
	if (!file)
		return (0);
	if (file[i + 1].token != FINISH)
		return (0);
	return (1);
}

int	trybuiltin(t_data *data, char **cmd)
{
	int	return_value;

	return_value = -1;
	if (!ft_ultracmp(cmd[0], "cd"))
		return_value = ft_cd(cmd, data->env);
	else if (!ft_ultracmp(cmd[0], "echo"))
		return_value = ft_echo(cmd);
	else if (!ft_ultracmp(cmd[0], "env"))
		return_value = ft_env(data->env);
	else if (!ft_ultracmp(cmd[0], "export"))
		return_value = ft_export(&data, cmd);
	else if (!ft_ultracmp(cmd[0], "exit"))
	{
		ft_exit(&data, cmd);
		return_value = data->exit[1];
	}
	else if (!ft_ultracmp(cmd[0], "pwd"))
		return_value = ft_pwd();
	else if (!ft_ultracmp(cmd[0], "unset"))
		return_value = ft_unset(&data, cmd);
	return (return_value);
}
