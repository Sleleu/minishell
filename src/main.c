/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/14 14:49:32 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		process(char *line, char **env)
{
	if (!line || line[0] == EOF)
	{
		ft_putstr_fd("\n", 2);
		free(line);
		return (0) ;
	}
	else if (ft_strlen(line) > 1)
	{
		if (!strcmp("pwd\n", line))
			ft_pwd();
		if (!strcmp("env\n", line))
			ft_env(env);
		if (!strcmp("exit\n", line))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (1);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line;

	while (1)
	{
		ft_putstr_fd("🌀\033[34m\e[1m minishell \033[0;31m>\033[33m>\033[0;32m>\033[0m ", 2);
		line = get_next_line(0);
		if (!process(line, env))
			break ;
	}
	return (0);
}