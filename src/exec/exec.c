/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:10:24 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/20 18:52:32 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		builtin(t_data **data)
{
	if ((*data)->line == NULL || !strcmp("exit", (*data)->line))
	{
		ft_putstr_fd("\n", 2);
		return (-1) ;
	}
	else if (ft_strlen((*data)->line) > 1)
	{
		if (!strcmp("pwd", (*data)->line))
			return (ft_pwd());
		else if (!strcmp("env", (*data)->line))
			return (ft_env((*data)->env));
		else if (!strncmp("cd", (*data)->line, ft_strlen("cd")))
			return (ft_cd((*data)->line));
		else if (!strncmp("echo", (*data)->line, ft_strlen("echo")))
			return (ft_echo((*data)->line));
		else if (!strncmp("unset", (*data)->line, ft_strlen("unset")))
			return (ft_unset((*data)->env, (*data)->line));
	}
	return (6);	
}

int		process(t_data **data)
{
	char	*cmd[3] = {"/usr/bin/ls", "-la", 0};
	int		test;
	
	test = builtin(data);
	if (test != 6)
		return (test);
	else
		execve(cmd[0], cmd, (*data)->env);
	return (1);
}
