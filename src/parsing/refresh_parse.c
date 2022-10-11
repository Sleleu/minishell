/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:30:54 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/11 02:21:33 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_parse_count(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_parse_sep(str, i))
			i++;
		if (str[i] && !is_parse_sep(str, i))
			count++;
		while (str[i] && !is_parse_sep(str, i))
			i++;
	}
	return (count);
}

char	*ft_parse_word(char *str, int i)
{
	int		j;
	int		len;
	int		size;
	char	*word;

	j = 0;
	len = 0;
	size = i;
	while (str[size] && !is_parse_sep(str, size))
	{
		len++;
		size++;
	}
	word = memcenter(MALLOC, sizeof(char) * (len + 1), NULL, PARSING);
	while (i < size)
	{
		word[j] = str[i];
		i++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_parse_split(char *str)
{
	int		i;
	int		j;
	int		count;
	char	**d_tab;

	i = 0;
	j = 0;
	count = ft_parse_count(str);
	d_tab = memcenter(MALLOC, sizeof(char *) * count + 1, NULL, PARSING);
	d_tab[count] = NULL;
	while (str && str[i])
	{
		while (str[i] && is_parse_sep(str, i))
			i++;
		if (str[i] && !is_parse_sep(str, i))
		{
			d_tab[j] = ft_parse_word(str, i);
			j++;
		}
		while (str[i] && !is_parse_sep(str, i))
			i++;
	}
	return (d_tab);
}

t_parse	*ft_check_space(t_parse *new_parse, t_parse parse)
{
	int		i;
	char	**d_tab;
	t_parse	new_token;

	i = 0;
	d_tab = ft_parse_split(parse.str);
	while (d_tab[i])
	{
		new_token.type = parse.type;
		new_token.cmd = parse.cmd;
		new_token.str = memcenter(MALLOC, sizeof(char)
				* (ft_strlen(d_tab[i]) + 1), NULL, PARSING);
		ft_strcpy(new_token.str, d_tab[i]);
		new_parse = ft_parsejoin(new_parse, new_token);
		memcenter(FREE, 0, new_token.str, PARSING);
		i++;
	}
	return (new_parse);
}

t_parse	*ft_refresh_parse(t_data **data)
{
	int		i;
	t_parse	*new_parse;

	i = 0;
	new_parse = NULL;
	while ((*data)->parse[i].type != FINISH)
	{
		if ((*data)->parse[i].str == NULL)
			new_parse = ft_parsejoin(new_parse, (*data)->parse[i]);
		else
			new_parse = ft_check_space(new_parse, (*data)->parse[i]);
		i++;
	}
	return (new_parse);
}
