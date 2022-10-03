/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/03 18:02:09 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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


static void free_while(void)
{
	memcenter(FREE_WHERE, 0, NULL, LEXER);
	memcenter(FREE_WHERE, 0, NULL, PARSING);
	memcenter(FREE_WHERE, 0, NULL, EXEC);
	//memcenter(FREE_WHERE, 0, NULL, BUILTIN);
}

/*
char	*ft_getenv(char **env)
{
	int	i;
	char *str;
	char *pwd;
	
	i = 0;
	while (ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")))
		i++;
	pwd = memcenter(MALLOC, sizeof(char) * ft_strlen(env[i]) + 1, 0, BUILTIN);
	ft_strcpy(pwd, env[i]);
	i = ft_strlen(getenv("HOME"));
	str = memcenter(MALLOC, sizeof(char) * ft_strlen(pwd) - (i + 1), 0, BUILTIN);
	str = ft_substr(pwd, i + 4, ft_strlen(pwd));
	str[ft_strlen(str)] = '\0';
	return (str);
}*/


int		main(int ac, char **av, char **env)
{
	(void)av;
	t_data	*data;
	
	if (ac != 1)
		return (0);
	data = set_data(env);
	while (1)
	{
		//ft_putstr_fd(ft_getenv(data->env), 1);
		//sig_init();
		data->line = readline("minishell >>> ");
		if (!data->line)
		{
			printf("\n");
			break ;
		} 
		if (data->line && ft_strlen(data->line) > 0)
			add_history(data->line);
		data->lexer = ft_lexer(data->line);
		if (is_line(data->line) && ft_parser(&data) != -1)
		{
			if (is_line(data->line) && process(&data) == -1)
				break ;
		}
		if (is_line(data->line))
			free_while();
		restore_data();
	}
	memcenter(PURGE, 0, NULL, NOTHING);
	return (0);
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