/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:17 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 23:42:32 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**find_path(char **e)
{
	int		i;
	char	**paths;

	if (!e[0])
		return (NULL);
	i = 0;
	while (e[i + 1] && (ft_strnstr(e[i], "PATH", 4) == 0 || e[i][4] != '='))
		i++;
	if (ft_strnstr(e[i], "PATH", 4) == 0 || e[i][4] != '=')
		return (NULL);
	paths = ft_split(e[i] + 5, ':');
	return (paths);
}

char	*find_cmdpath(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	paths = find_path(envp);
	if (!paths)
		return (0);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	free_double(paths);
	return (0);
}

char	**test(char **lol)
{
	char	**test;
	int		i;

	i = 0;
	while (lol[i] != NULL)
		i++;
	test = (char **)malloc(sizeof(char *) * (i + 3));
	if (!test)
		return (NULL);
	test[0] = (char *)malloc(sizeof(char) * ft_strlen("bash") + 1);
	if (!test[0])
		return (NULL);
	test[0] = "/usr/bin/bash\0";
	i = 0;
	while (lol[i] != NULL)
	{
		test[i + 1] = (char *)malloc(sizeof(char) * ft_strlen(lol[i]) + 1);
		if (!test[i + 1])
			return (NULL);
		test[i + 1] = lol[i];
		i++;
	}
	test[i + 1] = NULL;
	return (test);
}

char	**getcmd(t_data *data, int cmdnb)
{
	int		i;
	int		words;
	int		w_copy;
	t_parse	*parse;
	char	**cmd;

	words = getwords(data, cmdnb);
	parse = data->parse;
	if (!words)
		return (NULL);
	cmd = memcenter(MALLOC, (sizeof(char *) * (words + 1)), NULL, EXEC);
	if (!cmd)
		return (NULL);
	i = -1;
	w_copy = words;
	while (words > 0 && parse[++i].type != FINISH)
	{
		if (parse[i].type == WORD && parse[i].cmd == cmdnb)
		{
			cmd[w_copy - words] = parse[i].str;
			words--;
		}
	}
	cmd[w_copy] = 0;
	return (cmd);
}
