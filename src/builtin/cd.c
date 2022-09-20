/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:12:50 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/20 19:02:31 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	replace_pwd(char *path)
{
	int i;
	char **env;

	i = 0;
	env = get_data()->env;
	while (env[i] && strncmp("PWD", env[i], 3) != 0)
		i++;
	env[i] = ft_strjoin("PWD=\0", path);
	if (!env[i])
		return ;
}

int	ft_cd(char *line)
{
	char	**cd;
	int		i;

	cd = memcenter(MALLOC, 0, ft_split(line, ' '), BUILTIN);
	if (!cd)
		return (0);
	i = 0;
	while (cd[i])
	{
		memcenter(MALLOC, 0, cd[i], BUILTIN);
		i++;
	}
	memcenter(MALLOC, 0, cd[i], BUILTIN);
	chdir(cd[1]);
	replace_pwd(cd[1]);
	return (1);
}