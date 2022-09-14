/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/14 20:14:58 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		process(char *line, char **env)
{
	if (line == NULL || !strcmp("exit", line)) // ctrl+D | exit
	{
		free(line);
		return (0) ;
	}
	else if (ft_strlen(line) > 1)
	{
		if (!strcmp("pwd", line))
			ft_pwd();
		else if (!strcmp("env", line))
			ft_env(env);
		else if (!strncmp("echo", line, ft_strlen("echo")))
			ft_echo(line);
		else if (!strncmp("unset", line, ft_strlen("unset")))
			ft_unset(env, line);
		free(line);
	}
	return (1);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*line = NULL;
	t_data	*data;
	
	data = set_data(env);
	printf("%d\n", data->nb);
	while (1)
	{
		line = readline("🌀\033[34m\e[1m minishell \033[0;31m>\033[33m>\033[0;32m>\033[0m ");
		if (line && ft_strlen(line) > 0)
			add_history(line);
		ft_parser(line);
		if (!process(line, env))
			break ;
	}
	free_struct();
	return (0);
}