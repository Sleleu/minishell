/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:19:43 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/03 16:42:05 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 	
		BOOL_QUOTE
	Si l'autre quote est deja active, on ne touche a rien. Si elle ne
	l'est pas, on active ou desactive le booleen
*/

void	bool_quote(int *quote1, int *quote2)
{
	if (*quote1 == 1)
		return ;
	else if (*quote2 == 0)
		*quote2 = 1;
	else if (*quote2 == 1)
		*quote2 = 0;
}

/*
		CHECK_ENV
	retourne l'index de la variable d'environnement avec str si elle existe
	Sinon, retourne -1
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
		if (!ft_strncmp(str, env[i], index_equal)
			&& ((int)ft_strlen(str) == index_equal))
			return (i);
		i++;
	}
	return (-1);
}

/*
		FT_VARCPY
	Copie str dans var de l'index i jusque j
*/

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

/*
		CHECK_DOLLAR
	Verifie si il y a une variable d'environnement dans la str
*/

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

/*
		FT_VARJOIN
	Substitue la variable d'env de str par sa valeur, 
	et retourne une new_str contenant cette valeur.
	- i contient la place de la variable d'environnement
	- Des que j termine de parcourir la variable, *var recupere la variable
	- Check si la variable se trouve dans l'env, si oui, index_var recupere sa place
	- env_ptr se place sur la variable d'environnement, et ++ jusqu'a sa valeur
	- On strjoin la valeur de la variable d'environnement a la new_str;
*/

char	*ft_varjoin(char *new_str, char *str, char **env, int *i)
{
	char	*env_ptr;
	char	*var;
	int		j;
	int		index_var;

	index_var = -1;
	j = *i;
	if (ft_isdigit(str[*i]))
		*i += 1;
	while (str[j])
	{
		if (str[j] && (is_space(str[j]) || !ft_isalpha(str[j])))
			break ;
		j++;
	}
	var = memcenter(MALLOC, sizeof(char) * (j - *i) + 1, 0, PARSING);
	ft_varcpy(var, str, i, j);
	index_var = check_env(env, var);
	env_ptr = env[index_var];
	env_ptr += ft_strlen(var) + 1;
	if (index_var != -1)
		new_str = ft_strjoin(new_str, env_ptr);
	else
		new_str = ft_strjoin(new_str, "");
	return (new_str);
}
