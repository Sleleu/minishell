/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:26:12 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/23 14:42:46 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	new_env = memcenter(MALLOC, sizeof(char *) * size + 2, NULL, BUILTIN);
	printf("%d\n", size);
	while ((*data)->env[index])
	{
		len = ft_strlen((*data)->env[index]);
		new_env[index] = memcenter(MALLOC, sizeof(char) * len + 1, NULL, BUILTIN);
		new_env[index][len] = '\0';
		ft_strcpy(new_env[index], (*data)->env[index]);
		index++;
	}
	new_env[index] = memcenter(MALLOC, sizeof(char) * ft_strlen((*data)->parse[i].str) + 1, NULL, BUILTIN);
	new_env[index][ft_strlen((*data)->parse[i].str) - 1] = '\0';
	new_env[index] = '\0';
	ft_strcpy(new_env[size - 1], (*data)->parse[i].str);
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
	
	j = 0;
	while ((*data)->parse[i].str[j])
	{
		if ((*data)->parse[i].str[j] == '=')
			return (j);
		j++;
	}
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

int	ft_export_check_arg(t_data **data)
{
	int	i;

	i = 0;
	while (ft_strncmp((*data)->parse[i].str, "export", ft_strlen("export")))
		i++;
	if (i != 0) // export doit etre au debut
		return (0);
	while ((*data)->parse[i].type != FINISH)
	{
		if ((*data)->parse[i].type != WORD) // verifier que export = seule commande
			return (0); // AJOUTER print des erreurs avant de return le 0 | CHECKER EXPAND ? le += avec dollar
		i++;
	}
	if (i == 1)
	{
		ft_env((*data)->env); // si export == 0 arg -> export affiche l'environnement
		return (0);
	}
	return (1);
}

int	ft_export(t_data **data)
{
	int	i;
	int code;
	int	index_equal;

	code = 0;
	index_equal = 0;
	if (ft_export_check_arg(data) == 0)
		return (0);
	i = 1;
	while ((*data)->parse[i].type == WORD)
	{
		if (!export_error((*data)->parse, i))
		{ 	
			index_equal = is_env_variable(data, i);
			if (index_equal != 0 && isalnum_var(data, i, index_equal))
				(*data)->env = ft_envjoin(data, i);
		}
		else
			code = 1;
		i++;
	}
	return (code);
}

// += append pour l'env
// export sans arg = afficher l'env