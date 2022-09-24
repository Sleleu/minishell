/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:11:11 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/24 20:40:48 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	len;

	len = nmemb * size;
	if (len / size != nmemb)
		return (NULL);
	str = memcenter(MALLOC, nmemb * size, NULL, NOTHING);
	if (!str)
		return (NULL);
	ft_bzero(str, nmemb * size);
	return (str);
}
