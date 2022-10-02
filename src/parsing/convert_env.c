/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:32:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/02 19:17:26 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (!ft_strncmp(str, env[i], index_equal) && ((int)ft_strlen(str) == index_equal))
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
		FT_VARJOIN
	Substitue la variable d'env de str par sa valeur, et retourne une new_str contenant cette valeur
	- i contient la place de la variable d'environnement
	- Des que j termine de parcourir la variable, *var recupere la variable
	- On verifie si la variable se trouve dans l'env, si oui, index_var recupere sa place
	- env_ptr se place sur la variable d'environnement, et s'incremente jusqu'a sa valeur
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

int	find_dollar_index(char *str, int end)
{
	int	i;
	int dollar_index;

	dollar_index = 0;
	i = 0;
	while (str[i] && i < end)
	{
		if (str[i] == '$')
			dollar_index++;
		i++;
	}
	return (dollar_index);
}

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
		ACTIVE_VAR
	On verifie avec le token du lexer si la variable d'environnement situe a
	l'index j est a l'interieur d'une simple quote ou non
*/

int		active_var(char *str, int j)
{
	int	i = 0;
	int	d_quote = 0;
	int	s_quote = 0;
	while (i < j)
	{
		if (str[i] == '"')
			bool_quote(&s_quote, &d_quote);
		else if (str[i] == 39)
			bool_quote(&d_quote, &s_quote);
		i++;
	}
	if (s_quote == 1)
		return (0);
	return (1);
}

/*
		DOLLAR_IN_SQUOTE
	La variable str etant deja parsee pour ne pas retirer les quotes dans les variables d'environnement,
	il faut recuperer le token d'origine pour compter les quotes.
	
	- index_parse est la place du token dans le lexer, on fait une boucle pour envoyer le ptr sur ce token
	- Plusieurs variables d'env peuvent se trouver dans la meme str, on doit donc trouver l'index du bon dollar
	avec find_dollar_index, et i qui contient la place du $ dans la str
	- Une fois le bon index de & sur la str, on le synchronise avec le dollar au meme endroit dans le lexer
	- On check sur ce $ si c'est une variable active = pas dans une simple quote
*/

int		dollar_in_squote(t_data **data, char *str, int i, int index_parse)
{
	int dollar_str;
	int dollar_lexer;
	int j;
	t_lexer *ptr;
	
	dollar_str = 0;
	dollar_lexer = 0;
	j = 0;
	ptr = (*data)->lexer;
	while (j++ < index_parse)
		ptr = ptr->next;
	dollar_str = find_dollar_index(str, i + 1);
	j = 0;
	while (ptr->content[j] && dollar_lexer < dollar_str)
	{
		if (ptr->content[j] == '$')
			dollar_lexer++;
		j++;
	}
	if (!active_var(ptr->content, j))
		return (1);
	return (0);
}

/*
		PARSE_DOLLAR
	Une nouvelle str va remplacer le texte dans le parser avec les variables d'environnement
	- Si c'est un $, non suivi d'un espace et n'etant pas dans des simples quotes : on
	substitue $ par la variable d'environnement
	- Si c'est du texte normal, on le charjoin	
*/

char	*parse_dollar(t_data **data, char **env, char *str, int index_parse)
{
	int	i;
	char *new_str;
	
	i = 0;
	new_str = NULL;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] && !is_space(str[i + 1])
			&& !dollar_in_squote(data, str, i, index_parse))
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

void	convert_env(t_data **data)
{
	int	i;
	
	i = 0;
	while (token_type(data, i) != FINISH)
	{
		if ((*data)->parse[i].str != NULL && check_dollar((*data)->parse[i].str))
			(*data)->parse[i].str = parse_dollar(data, (*data)->env, (*data)->parse[i].str, i);
		i++;
	}
}