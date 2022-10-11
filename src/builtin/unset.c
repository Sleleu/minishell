/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:51:49 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 21:20:31 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_unset_env(char **env, int index_var)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	new_env = memcenter(MALLOC, sizeof(char *) * (i), NULL, BUILTIN);
	i = 0;
	while (env[i])
	{
		if (i == index_var && i == 0)
			i++;
		new_env[j] = memcenter(MALLOC, sizeof(char)
				* (ft_strlen(env[i]) + 1), NULL, BUILTIN);
		ft_strcpy(new_env[j], env[i]);
		i++;
		j++;
		if (i == index_var)
			i++;
	}
	new_env[i - 1] = '\0';
	return (new_env);
}

int	ft_unset(t_data **data, char **cmd)
{
	int	i;
	int	index_var;

	i = 0;
	index_var = 0;
	while (cmd[i])
	{
		index_var = is_new_var((*data)->env, cmd[i]);
		if (index_var != -1)
			(*data)->env = ft_unset_env((*data)->env, index_var);
		i++;
	}
	return (0);
}
