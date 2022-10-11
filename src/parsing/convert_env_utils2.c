/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:46:46 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/11 02:24:05 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
		IS_PARSE_SEP
	differencie dans un token les espaces etant des separateurs, et les
	espaces dans des quotes
*/

int	is_parse_sep(char *str, int i)
{
	int	d_quote;
	int	s_quote;
	int	j;

	j = 0;
	d_quote = 0;
	s_quote = 0;
	while (j < i)
	{
		if (str[j] == 39)
			bool_quote(&d_quote, &s_quote);
		else if (str[j] == '"')
			bool_quote(&s_quote, &d_quote);
		j++;
	}
	if (is_space(str[i]) && d_quote == 0 && s_quote == 0)
		return (1);
	return (0);
}

/*
		FT_STRJOIN_ENV
	ajoute des quotes inverses a la quote trouvee dans la valeur d'une
	variable d'env afin de preserver les guillemets dans le parse_quote
*/

char	*ft_strjoin_env(char *new_str, char *env_ptr)
{
	int	i;

	i = 0;
	while (env_ptr[i])
	{
		if (env_ptr[i] == 39)
		{
			new_str = ft_charjoin(new_str, '"');
			new_str = ft_charjoin(new_str, env_ptr[i]);
			new_str = ft_charjoin(new_str, '"');
		}
		else if (env_ptr[i] == '"')
		{
			new_str = ft_charjoin(new_str, 39);
			new_str = ft_charjoin(new_str, env_ptr[i]);
			new_str = ft_charjoin(new_str, 39);
		}
		else
			new_str = ft_charjoin(new_str, env_ptr[i]);
		i++;
	}
	return (new_str);
}

/*
		FT_CODEJOIN
	Substitue la variable $? au code de retour
*/

char	*ft_codejoin(t_data **data, char *new_str, int *i)
{
	char	*str_code;

	*i += 2;
	str_code = ft_itoa((*data)->exit[1]);
	new_str = ft_strjoin(new_str, str_code);
	return (new_str);
}

/*
		FT_STRUCTCPY
	copie dans la structure dest le contenu de la structure src
*/

t_parse	ft_structcpy(t_parse dest, t_parse src)
{
	if (src.str != NULL)
	{
		dest.str = memcenter(MALLOC, sizeof(char)
				* (ft_strlen(src.str) + 1), NULL, PARSING);
		ft_strcpy(dest.str, src.str);
	}
	else
		dest.str = NULL;
	dest.type = src.type;
	dest.cmd = src.cmd;
	return (dest);
}

/*
		FT_PARSEJOIN
	Join au tableau de structure de type parse une nouvelle
	de type structure parse, ainsi que le type FINISH terminant
	le tableau
*/

t_parse	*ft_parsejoin(t_parse *new_parse, t_parse parse)
{
	int		i;
	int		size;
	t_parse	*new_struct;

	i = 0;
	size = 0;
	while (new_parse && new_parse[size].type != FINISH)
		size++;
	new_struct = memcenter(MALLOC, sizeof(t_parse) * (size + 2), NULL, PARSING);
	while (new_parse && new_parse[i].type != FINISH)
	{
		new_struct[i] = ft_structcpy(new_struct[i], new_parse[i]);
		i++;
	}
	new_struct[i] = ft_structcpy(new_struct[i], parse);
	i++;
	new_struct[i].str = NULL;
	new_struct[i].type = FINISH;
	new_struct[i].cmd = parse.cmd;
	return (new_struct);
}
