/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:51:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/03 20:49:42 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_unset(char **env, char **cmd)
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
	(void)env;
	(void)cmd;
	return (0);
}

/*
char **ft_unset_env(char **env, int index_var)
{
	int	i;
	int	j;
	int	size;
	char **new_env;
	
	i = 0;
	j = 0;
	size = 0;
	while (env[size])
		size++;
	new_env = memcenter(MALLOC, sizeof(char *) * (size + 1), NULL, BUILTIN);
	while (env[i])
	{
		new_env[j] = memcenter(MALLOC, sizeof(char)
			* (ft_strlen(env[i] + 1)), NULL, BUILTIN);
		ft_strcpy(new_env[j], env[i]);
		i++;
		j++;
		if (i == index_var)
			i++;
	}
	new_env[size] = '\0';
	return (new_env);
}

int ft_unset(t_data **data, char **cmd)
{
	int	i;
	int	index_var;

	i = 1;
	index_var = 0;
	while (cmd[i])
	{
		index_var = is_new_var((*data)->env, cmd[i]);
		if (index_var != -1)
			(*data)->env = ft_unset_env((*data)->env, index_var);
		i++;
	}
	return (0);
}*/
