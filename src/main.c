/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/13 17:42:49 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_global	g_sigstatus;

int	is_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (1);
		i++;
	}
	return (0);
}

void	free_while(void)
{
	memcenter(FREE_WHERE, 0, NULL, LEXER);
	memcenter(FREE_WHERE, 0, NULL, PARSING);
	memcenter(FREE_WHERE, 0, NULL, EXEC);
}

char	**set_env(char **env)
{
	char	pwd[PATH_MAX];

	env = ft_envjoin(env, ft_strjoin("PWD=", getcwd(pwd, sizeof(pwd))));
	env = ft_envjoin(env, ft_strjoin("SHLVL=", "1"));
	env = ft_envjoin(env, ft_strjoin("_=", "/usr/bin/env"));
	return (env);
}

void	ft_minishell(t_data *data)
{
	while (g_sigstatus.value)
	{
		sig_init();
		data->line = readline("minishell >>> ");
		if (!data->line)
		{
			printf("exit\n");
			break ;
		}
		if (data->line && ft_strlen(data->line) > 0)
			add_history(data->line);
		data->lexer = ft_lexer(data->line);
		if (is_line(data->line) && ft_parser(&data) != -1)
		{
			if (is_line(data->line))
			{
				process(&data);
				if (data->exit[0])
					break ;
			}
		}
		if (is_line(data->line))
			free_while();
		restore_data();
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)av;
	if (ac != 1)
		return (0);
	if (!env[0])
		env = set_env(env);
	data = set_data(env);
	g_sigstatus.process = 0;
	g_sigstatus.value = 1;
	g_sigstatus.code = &data->exit[1];
	ft_minishell(data);
	memcenter(PURGE, 0, NULL, NOTHING);
	return (data->exit[1]);
}

/*
Execution Pipes => 

Partout :
	pwd
	env
	export
	echo

En dernier : 
	export yo=yo
	unset yo=yo
	cd
*/