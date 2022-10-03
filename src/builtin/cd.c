/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:12:50 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/03 23:14:50 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i] && strncmp(str, env[i], ft_strlen(str)) != 0)
		i++;
	return (env[i] + (ft_strlen(str) + 1));
}

static void	replace_pwd(char *path, char **env)
{
	int	i;

	i = 0;
	while (env[i] && strncmp("PWD", env[i], 3) != 0)
		i++;
	env[i] = ft_strjoin("PWD=\0", path);
	if (!env[i])
		return ;
}

int	ft_cd(char *path, char **env)
{
	if (!path)
	{
		chdir(ft_getenv(env, "HOME"));
		replace_pwd(ft_getenv(env, "HOME"), env);
	}
	else
	{
		if (chdir(path) == -1)
			perror(path);
		else
			replace_pwd(path, env);
	}
	return (1);
}
