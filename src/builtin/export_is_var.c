/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_is_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:49:41 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/11 15:15:04 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_env_variable(char *str, int *code)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (i == 0)
			{
				printf("minishell: export: `%s", str);
				printf("':not a valid identifier\n");
				*code = 1;
				return (0);
			}
			else
				return (i);
		}
		i++;
	}
	return (0);
}

int	isalnum_var(char *str, int index_equal)
{
	int	i;

	i = 0;
	while (i < index_equal)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			if (i > 0 && str[i] == '+' && str[i + 1] == '=')
				return (2);
			else
			{
				printf("minishell: export: `%s", str);
				printf("':not a valid identifier\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	is_new_var(char **env, char *str)
{
	int	i;
	int	index_equal_env;
	int	index_equal_str;

	i = 0;
	index_equal_str = 0;
	while (str[index_equal_str] && str[index_equal_str] != '=')
		index_equal_str++;
	while (env[i])
	{
		index_equal_env = 0;
		while (env[i][index_equal_env] && env[i][index_equal_env] != '=')
			index_equal_env++;
		if (!ft_strncmp(str, env[i], index_equal_str)
			 && index_equal_env == index_equal_str)
			return (i);
		i++;
	}
	return (-1);
}
