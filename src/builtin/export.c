/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:26:12 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/23 18:21:44 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_envjoin(t_data **data, char *str)
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
	while ((*data)->env[index])
	{
		len = ft_strlen((*data)->env[index]);
		new_env[index] = memcenter(MALLOC, sizeof(char) * len + 1, NULL, BUILTIN);
		new_env[index][len] = '\0';
		ft_strcpy(new_env[index], (*data)->env[index]);
		index++;
	}
	new_env[index] = memcenter(MALLOC, sizeof(char) * ft_strlen(str) + 1, NULL, BUILTIN);
	new_env[index + 1] = '\0';
	ft_strcpy(new_env[index], str);
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
			if ((*data)->parse[i].str[j] == '+' && (*data)->parse[i].str[j + 1] == '=')
			{
				return (2);
			}
			else
			{
				printf("minishell: export: `%s", (*data)->parse[i].str);
				printf("':not a valid identifier\n");
				return (0);
			}
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

int	is_new_var(t_data **data, char *str, int index_equal)
{
	int j;

	j = 0;
	while ((*data)->env[j])
	{
		if (!ft_strncmp(str, (*data)->env[j], index_equal))
			return (j);
		j++;
	}
	return (0);
}

void	ft_refresh_var(t_data **data, char *str, int index_equal)
{
	int index_var;

	index_var = is_new_var(data, str, index_equal);
	free((*data)->env[index_var]);
	ft_strjoin((*data)->env[index_var], str);
}

/*
void	ft_append_var(t_data **data, char *str, int index_equal)
{
	int	i;
	char *append_str;

		ft_envjoin(data, str);
	// go substr avec le = et strjoin la suite de la variable
}*/

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
			if (index_equal != 0 && isalnum_var(data, i, index_equal) == 1)
			{
				if (is_new_var(data, (*data)->parse[i].str, index_equal) == 0)
					(*data)->env = ft_envjoin(data, (*data)->parse[i].str);
				else
					ft_refresh_var(data, (*data)->parse[i].str, index_equal);
			}
			//else if (index_equal != 0 && isalnum_var(data, i, index_equal) == 2) // il y a un +=
			//	ft_append_var(data, (*data)->parse[i].str, index_equal);
		}
		else
			code = 1;
		i++;
	}
	return (code);
}

//segfault si change une variable existant deja au tout debut
// += append pour l'env
// export sans arg = afficher l'env