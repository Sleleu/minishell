/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:26:12 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/24 21:49:15 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_error_num(t_parse *parse, int i)
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

int	ft_export_check_arg(t_data **data, t_parse *parse)
{
	int	i;

	i = 0;
	while (ft_strncmp(parse[i].str, "export", ft_strlen("export")))
		i++;
	if (i != 0)
		return (0);
	while (parse[i].type != FINISH)
	{
		if (parse[i].type != WORD)
			return (0);
		i++;
	}
	if (i == 1)
	{
		ft_env((*data)->env);
		return (0);
	}
	return (1);
}

void	ft_refresh_var(t_data **data, char *str, int index_equal)
{
	int		index_var;
	char	*new_var;
	char	*new_value;

	index_var = is_new_var((*data)->env, str, index_equal);
	new_var = ft_substr((*data)->env[index_var], 0, index_equal + 1);
	new_value = ft_substr(str, index_equal + 1, ft_strlen(str));
	ft_strjoin(new_var, new_value);
	(*data)->env[index_var] = ft_strjoin(new_var, new_value);
}

void	ft_export_action(t_data **data, char *str, int index_equal)
{
	if (isalnum_var(str, index_equal) == 1)
	{
		if (is_new_var((*data)->env, str, index_equal) == 0)
			(*data)->env = ft_envjoin((*data)->env, str);
		else
			ft_refresh_var(data, str, index_equal);
	}
	else if (isalnum_var(str, index_equal) == 2)
		(*data)->env = ft_append_var((*data)->env, str, index_equal);
}

int	ft_export(t_data **data, t_parse *parse)
{
	int	i;
	int	code;
	int	index_equal;

	i = 1;
	code = 0;
	index_equal = 0;
	if (ft_export_check_arg(data, parse) == 0)
		return (0);
	while (parse[i].type == WORD)
	{
		index_equal = is_env_variable(parse[i].str, &code);
		if (isalnum_var(parse[i].str, index_equal)
			&& !export_error_num(parse, i))
		{
			if (index_equal != 0 && is_env_variable(parse[i].str, &code))
				ft_export_action(data, parse[i].str, index_equal);
		}
		else
			code = 1;
		i++;
	}
	return (code);
}
