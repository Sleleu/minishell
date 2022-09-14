/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:35:34 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/14 14:49:04 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(char *line)
{
	char	**result;
	int		i;
	
	i = 1;
	result = ft_split(line, ' ');
	while (result[i])
	{
		printf("%s ", result[i]);
		i++;
	}
	free(result);
	return (1);
}


// int	ft_echo(char *line)
// {
// 	int i;

// 	i = 1;
// 	if (argc > 1)
// 	{
// 		while (argv[i])
// 		{
// 			printf("%s", argv[i]);
// 			if (argv[i + 1])
// 				printf(" ");
// 			i++;	
// 		}
// 		printf("\n");
// 		return (1);
// 	}
// 	else
// 		return (0);
// }