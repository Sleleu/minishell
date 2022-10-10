/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:12:50 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/10 20:50:04 by rvrignon         ###   ########.fr       */
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

int	ft_cd(char **arg, char **env)
{
	char *path;

	path = arg[1];
	if (!path)
	{
		chdir(ft_getenv(env, "HOME"));
		replace_pwd(ft_getenv(env, "HOME"), env);
	}
	if (arg[2])
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	else
	{
		if (chdir(path) == -1)
		{
			perror(path);
			return (1);
		}
		else
			replace_pwd(path, env);
	}
	return (0);
}
