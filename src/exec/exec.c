/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:10:24 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/20 18:10:42 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		process(t_data **data)
{
	if ((*data)->line == NULL || !strcmp("exit", (*data)->line))
	{
		ft_putstr_fd("\n", 2);
		return (0) ;
	}
	else if (ft_strlen((*data)->line) > 1)
	{
		if (!strcmp("pwd", (*data)->line))
			ft_pwd();
		else if (!strcmp("env", (*data)->line))
			ft_env((*data)->env);
		else if (!strncmp("echo", (*data)->line, ft_strlen("echo")))
			ft_echo((*data)->line);
		else if (!strncmp("unset", (*data)->line, ft_strlen("unset")))
			ft_unset((*data)->env, (*data)->line);
	}
	return (1);
}
