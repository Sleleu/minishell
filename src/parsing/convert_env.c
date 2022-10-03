/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:32:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/03 17:52:58 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_dollar_index(char *str, int end)
{
	int	i;
	int	dollar_index;

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
		ACTIVE_VAR
	On verifie avec le token du lexer si la variable d'environnement situe a
	l'index j est a l'interieur d'une simple quote ou non
*/

int	active_var(char *str, int j)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
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
	La variable str etant deja parsee pour ne pas retirer les quotes dans
	les variables d'environnement, il faut recuperer token pour compter les quotes.
	
	- index_parse est la place du token dans le lexer, on fait une boucle pour
	envoyer le ptr sur ce token
	- Plusieurs variables d'env peuvent se trouver dans la meme str,
	on doit donc trouver l'index du bon dollar
	avec find_dollar_index, et i qui contient la place du $ dans la str
	- Une fois le bon index de str, synchro avec le $ au meme endroit dans le lexer
	- On check sur ce $ si c'est une variable active = pas dans une simple quote
*/

int	dollar_in_squote(t_data **data, char *str, int i, int index_parse)
{
	int		dollar_str;
	int		dollar_lexer;
	int		j;
	t_lexer	*ptr;

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
	Une nouvelle str va remplacer le texte dans le parser avec les variables d'env
	- Si c'est un $, non suivi d'un espace et n'etant pas dans des simples quotes on
	substitue $ par la variable d'environnement
	- Si c'est du texte normal, on le charjoin	
*/

char	*parse_dollar(t_data **data, char **env, char *str, int index_parse)
{
	int		i;
	char	*new_str;

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
void	refresh_parsing(t_data **d)
{
	int	i;
	
	i = 0;
	t_parse *new_parse;
	while ((*d)->parse[i].type != FINISH)
	{
		if ()
		i++;
	}
}*/

/*
		CONVERT_ENV
	Si la str du parser est pas vide, et qu'il y a une variable d'env, parse_dollar
*/

void	convert_env(t_data **data)
{
	int	i;

	i = 0;
	while (token_type(data, i) != FINISH)
	{
		if ((*data)->parse[i].str != NULL
			&& check_dollar((*data)->parse[i].str))
			(*data)->parse[i].str = parse_dollar(data, (*data)->env,
					(*data)->parse[i].str, i);
		i++;
	}
	//refresh_parsing(data);
}
