/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:12:50 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/13 17:42:08 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(str, env[i], ft_strlen(str)) != 0)
		i++;
	if (!env[i] || ft_strncmp(str, env[i], ft_strlen(str)) != 0)
		return (NULL);
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

int	null_path(char **env)
{
	chdir(ft_getenv(env, "HOME"));
	replace_pwd(ft_getenv(env, "HOME"), env);
	return (0);
}

int	ft_cd(char **arg, char **env)
{
	char	*path;
	char	pwd[PATH_MAX];

	path = arg[1];
	if (!path)
		return (null_path(env));
	if (!ft_ultracmp(path, "-"))
		return (ft_pwd());
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
			replace_pwd(getcwd(pwd, sizeof(pwd)), env);
	}
	return (0);
}
