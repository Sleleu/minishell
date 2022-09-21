/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/21 16:05:21 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		main(int ac, char **av, char **env)
{
	(void)av;
	char	*line;
	t_data	*data;
	
	if (ac != 1)
		return (0);
	data = set_data(env);
	while (1)
	{
		line = readline("🌀\033[34m\e[1m minishell \033[0;31m>\033[33m>\033[0;32m>\033[0m ");
		if (line && ft_strlen(line) > 0)
			add_history(line);
		data->line = line;
		data->lexer = ft_lexer(line);
		ft_parser(&data);
		if (process(&data) == -1)
			break ;
		memcenter(FREE_WHERE, 0, NULL, LEXER);
	}
	memcenter(PURGE, 0, NULL, NOTHING);
	return (0);
}
