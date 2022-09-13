/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:52:26 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/13 20:53:34 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == *little)
		{
			if (ft_strncmp(big + i, little, ft_strlen(little)) == 0
				&& ft_strlen(little) + i <= len)
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}
