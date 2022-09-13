/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/13 20:40:12 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char	*line;
	while (42)
	{
		ft_putstr_fd("🌀\033[34m\e[1m minishell \033[0;31m>\033[33m>\033[0;32m>\033[0m ", 1);
		line = get_next_line(0);
	//	readline(line);
	//	add_history(line);
		if (!strcmp("exit\n", line))
		{
			free(line);
			break;
		}
		else if (!strcmp("pwd\n", line))
			ft_pwd();
	//	parser(line);
		free(line);
	}
	return (0);
}