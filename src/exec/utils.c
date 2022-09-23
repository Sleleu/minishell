/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:11:15 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/23 18:22:14 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		builtin(t_data **data)
{
	if ((*data)->line == NULL || !strcmp("exit", (*data)->line))
		return (-1) ;
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
		else if (!strncmp("export", (*data)->line, ft_strlen("export")))
			return (ft_export(data));
	}
	return (6);	
}