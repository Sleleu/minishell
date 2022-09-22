/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:26:12 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/22 19:50:00 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_env(t_data **data)
{
	int	i;

	i = 0;
	while ((*data)->env[i])
	{
		memcenter(FREE, 0, (*data)->env[i], BUILTIN);
		i++;
	}
	memcenter(FREE, 0, (*data)->env, BUILTIN);
}

char	**ft_envjoin(t_data **data, int i)
{
	char **new_env;
	int	size;
	int index;
	int	len;
	
	size = 0;
	index = 0;
	len = 0;
	while ((*data)->env[size])
		size++;
	//new_env = memcenter(MALLOC, sizeof(char *) * size + 2, NULL, BUILTIN);
	new_env = malloc(sizeof(char *) * size + 2);
	while ((*data)->env[index])
	{
		len = ft_strlen((*data)->env[index]);
		//new_env[index] = memcenter(MALLOC, sizeof(char) * ft_strlen((*data)->env[index]) + 1, NULL, BUILTIN);
		new_env[index] = malloc(sizeof(char) * len + 1);
		new_env[index][len] = '\0';
		ft_strcpy(new_env[index], (*data)->env[index]);
		index++;
	}
	//new_env[index] = memcenter(MALLOC, sizeof(char) * ft_strlen((*data)->parse[i].str) + 1, NULL, BUILTIN);
	new_env[index] = malloc(sizeof(char) * ft_strlen((*data)->parse[i].str) + 1);
	new_env[index][ft_strlen((*data)->parse[i].str) - 1] = '\0';
	new_env[index] = '\0';
	ft_strcpy(new_env[size - 1], (*data)->parse[i].str);
	//ft_free_env(data);
	return (new_env);
}

int	export_error(t_parse *parse, int i)
{
	int	j;

	j = 0;
	if (ft_isdigit(parse[i].str[0]))
	{
		printf("minishell: export: `");
		while (parse[i].str[j] && ft_isdigit(parse[i].str[j]))
		{
			printf("%c", parse[i].str[j]);
			j++;
		}
		printf("':not a valid identifier\n");
		return (1);
	}
	return (0);
}

int	is_env_variable(t_data **data, int i)
{
	int	j;
	int	is_equal;
	
	j = 0;
	is_equal = 0;
	while ((*data)->parse[i].str[j])
	{
		if ((*data)->parse[i].str[j] == '=')
			is_equal = 1;
		j++;
	}
	if (is_equal == 1)
		return (j);
	else
		return (0);
}

int	isalnum_var(t_data **data, int i, int index_equal)
{
	int j;
	
	j = 0;
	while (j < index_equal)
	{
		if (!ft_isalnum((*data)->parse[i].str[j]))
		{
			printf("minishell: export: `%s", (*data)->parse[i].str);
			printf("':not a valid identifier\n");
			return (0);
		}
		j++;
	}
	return (1);
}

int	ft_export(t_data **data)
{
	int	i;
	int code;
	//int	index_equal;
	
	i = 0;
	code = 0;
	//index_equal = 0;
	while (ft_strncmp((*data)->parse[i].str, "export", ft_strlen("export")))
		i++;
	if (i != 0) // export doit etre au debut
		return (0);
	while ((*data)->parse[i].type != FINISH)
	{
		if ((*data)->parse[i].type != WORD) // verifier que export = seule commande
			return (0);
		i++;
	}
	i = 1;
	while ((*data)->parse[i].type == WORD)
	{
		if (!export_error((*data)->parse, i))
		{ 	
			//index_equal = is_env_variable(data, i);
			//if (index_equal != 0 && isalnum_var(data, i, index_equal))
				(*data)->env = ft_envjoin(data, i);
		}
		else
			code = 1;
		i++;
	}
	return (code);
}