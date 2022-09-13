/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:25:37 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/09 17:22:29 by sleleu           ###   ########.fr       */
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
		if (!strcmp("exit\n", line))
		{
			free(line);
			break;
		}
		free(line);
	}
	return (0);
}
/* paths, home user, split avec egal, pb, il y a egal et aussi des egals dans...
T'as le nom de la structure
env te sort des trucs comme user, ensuite home
arg = split[0]
path = split[1]
si l'aerg = usr ou home on stock dans une struct
*/