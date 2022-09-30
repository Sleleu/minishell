/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/30 14:21:00 by rvrignon         ###   ########.fr       */
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
		if (!line)
			break ; 
		if (line && ft_strlen(line) > 0)
			add_history(line);
		data->line = line;
		data->lexer = ft_lexer(line);
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
