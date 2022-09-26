/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/26 21:25:45 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void free_while(void)
{
	memcenter(FREE_WHERE, 0, NULL, LEXER);
	memcenter(FREE_WHERE, 0, NULL, PARSING);
	memcenter(FREE_WHERE, 0, NULL, EXEC);
	memcenter(FREE_WHERE, 0, NULL, BUILTIN);
}

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
		line = readline("minishell >>> ");
		if (line && ft_strlen(line) > 0)
			add_history(line);
		data->line = line;
		data->lexer = ft_lexer(line);
		if (ft_parser(&data) == -1)
			break ;
		if (process(&data) == -1)
			break ;
		free_while();
		restore_data();
	}
	memcenter(PURGE, 0, NULL, NOTHING);
	return (0);
}
