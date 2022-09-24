/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:00:03 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/24 20:52:00 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_envjoin(char **env, char *str)
{
	char **new_env;
	int	size;
	int index;
	int	len;
	
	size = 0;
	index = 0;
	len = 0;
	while (env[size])
		size++;
	new_env = memcenter(MALLOC, sizeof(char *) * (size + 2), NULL, BUILTIN);
	while (env[index])
	{
		len = ft_strlen(env[index]);
		new_env[index] = memcenter(MALLOC, sizeof(char) * (len + 1), NULL, BUILTIN);
		ft_strcpy(new_env[index], env[index]);
		index++;
	}
	new_env[size] = memcenter(MALLOC, sizeof(char) * (ft_strlen(str) + 1), NULL, BUILTIN);
	new_env[size + 1] = '\0';
	ft_strcpy(new_env[size], str);
	return (new_env);
}

// retourne une chaine de caractere sans le caractere specifiee en parametre, jusque n caractere

char *ft_strdel(char *str, char c, int n)
{
	char *new_str;
	int	i;
	int	j;

	i = 0;
	j = 0;
	new_str = memcenter(MALLOC, sizeof(char) * ft_strlen(str) + 1, NULL, BUILTIN);
	while (str[i])
	{
		if (str[i] == c && i < n)
			i++;
		new_str[j] = str[i];
		j++;	
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	**ft_append_var(char **env, char *str, int index_equal)
{
	char *parsed_str;
	int	index_var;
	char *append_str;
	
	parsed_str = ft_strdel(str, '+', index_equal);
	index_var = is_new_var(env, parsed_str, index_equal);
	if (!index_var)
		env = ft_envjoin(env, parsed_str);
	else
	{
		append_str = ft_substr(str, index_equal + 1, ft_strlen(str));
		env[index_var] = ft_strjoin(env[index_var], append_str);
	}
	return (env);
}