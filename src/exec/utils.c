/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:11:15 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/26 13:16:37 by rvrignon         ###   ########.fr       */
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

int		builtin(t_data **data)
{
	if ((*data)->line == NULL || !strncmp("exit", (*data)->line, ft_strlen("exit")))
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
			return (ft_echo((*data)->parse));
		else if (!strncmp("unset", (*data)->line, ft_strlen("unset")))
			return (ft_unset((*data)->env, (*data)->line));
		else if (!strncmp("export", (*data)->line, ft_strlen("export")))
			return (ft_export(data, (*data)->parse));
	}
	return (6);	
}