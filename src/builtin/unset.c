/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:51:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/10 21:08:55 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_unset(t_data **data, char **cmd)
{
	// char	**path;
	// int		i;

	// i = 0;
	// path = ft_split(line, ' ');
	// while (env[i])
	// {
	// 	if (!strncmp(path[1], env[i], ft_strlen(path[1]) - 1))
	// 		break ;
	// 	i++;
	// }
	// printf("%s", env[i]);
	(void)*data;
	(void)cmd;
	return (0);
}

/*
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_unset(env, "unset PWD");
	return (0);
}*/