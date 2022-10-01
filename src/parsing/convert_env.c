/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:32:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/01 06:18:20 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
int	check_env(char **env, char *str)
{
	int	i;
	int	index_equal;

	i = 0;
	while (env[i])
	{
		index_equal = 0;
		while (env[i][index_equal] && env[i][index_equal] != '=')
			index_equal++;
		if (!ft_strncmp(str, env[i], index_equal) && !str[index_equal])
			return (i);
		i++;
	}
	return (-1);
}

void	ft_structcpy(t_parse *dest, t_parse *src)
{
	dest->str = src->str;
	dest->type = src->type;
	dest->cmd = src->cmd;
}

t_parse	*assign_new_value(t_data **data, t_parse *new_parse, char *value)
{
	int	change;
	int	i;
	int	j;

	i = 0;
	j = 0;
	change = 0;
	while ((*data)->parse[i].type != FINISH)
	{
		if ((*data)->parse[i].type == DOLLAR && change == 0)
		{
			new_parse[j].str = value;
			new_parse[j].type = 1;
			new_parse[j].cmd = (*data)->parse[i].cmd;
			change = 1;
			i++;
		}
		else
			ft_structcpy(&new_parse[j], &(*data)->parse[i]);
		i++;
		j++;
	}
	ft_structcpy(&new_parse[j], &(*data)->parse[i]);
	return (new_parse);
}

t_parse	*change_parser(t_data **data, char *env_value)
{
	t_parse	*new_parse;
	int		i;
	int		size;
	char	*value;

	i = 0;
	size = 0;
	while (env_value[i] && env_value[i] != '=')
		i++;
	value = ft_substr(env_value, i + 1, ft_strlen(env_value));
	while ((*data)->parse[size].type != FINISH)
		size++;
	new_parse = memcenter(MALLOC, sizeof(t_parse) * size + 1, NULL, PARSING);
	new_parse = assign_new_value(data, new_parse, value);
	return (new_parse);
}

void	convert_env(t_data **data)
{
	int	i;
	int	index_var;

	i = 0;
	index_var = 0;
	while (token_type(data, i) != FINISH)
	{
		if (token_type(data, i) == DOLLAR)
		{
			index_var = check_env((*data)->env, (*data)->parse[i + 1].str);
			if (index_var == -1)
				return ;
			else
				(*data)->parse = change_parser(data, (*data)->env[index_var]);
		}
		i++;
	}
}
*/

int	check_env(char **env, char *str)
{
	int	i;
	int	index_equal;

	i = 0;
	while (env[i])
	{
		index_equal = 0;
		while (env[i][index_equal] && env[i][index_equal] != '=')
			index_equal++;
		if (!ft_strncmp(str, env[i], index_equal) && ((int)ft_strlen(str) == index_equal))
			return (i);
		i++;
	}
	return (-1);
}

void	ft_varcpy(char *var, char *str, int *i, int j)
{
	int	k;

	k = 0;
	while (*i < j)
	{
		var[k] = str[*i];
		*i += 1;
		k++;
	}
	var[k] = '\0';
}

char	*ft_varjoin(char *new_str, char *str, char **env, int *i)
{
	char	*env_ptr;
	char	*var;
	int		j;
	int		index_var;

	index_var = -1;
	j = *i;
	while (str[j])
	{
		if (str[j] && (is_space(str[j]) || !ft_isalpha(str[j]))) // on choppe la variable
			break;
		j++;
	}
	var = memcenter(MALLOC, sizeof(char) * (j - *i) + 1, 0, PARSING);
	ft_varcpy(var, str, i, j);
	index_var = check_env(env, var);
	env_ptr = env[index_var];
	env_ptr += ft_strlen(var) + 1;
	if (index_var != -1)
		new_str = ft_strjoin(new_str, env_ptr); // join la variable
	else
		new_str = ft_strjoin(new_str, ""); // rendre une string vide
	return (new_str);
}

char	*parse_dollar(char **env, char *str)
{
	int	i;
	char *new_str;
	
	i = 0;
	new_str = NULL;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] && !is_space(str[i + 1]))
		{
			i++;
			new_str = ft_varjoin(new_str, str, env, &i);
		}
		else
		{
			new_str = ft_charjoin(new_str, str[i]);
			i++;
		}
	}
	return (new_str);
}

int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && !is_space(str[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

void	convert_env(t_data **data)
{
	int	i;
	
	i = 0;
	while (token_type(data, i) != FINISH)
	{
		if ((*data)->parse[i].str != NULL && check_dollar((*data)->parse[i].str))
			(*data)->parse[i].str = parse_dollar((*data)->env, (*data)->parse[i].str);
		i++;
	}
}