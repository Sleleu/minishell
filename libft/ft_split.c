/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:48:25 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/24 19:55:55 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_word(char const *s, char c)
{
	int		i;
	int		size;
	char	*word;

	i = 0;
	size = 0;
	while (s[size] && s[size] != c)
		size++;
	word = ft_calloc(sizeof(char), size + 1);
	if (word == NULL)
		return (NULL);
	while (i < size)
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**split;

	i = 0;
	count = ft_count(s, c);
	split = ft_calloc(sizeof(char *), count + 1);
	if (split == NULL)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			split[i] = ft_word(s, c);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	return (split);
}
