/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:35:34 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/25 01:51:28 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(t_parse *parse)
{
	int		i;
	
	i = 1;
	while (parse[i].type == WORD)
	{
		printf("%s ", parse[i].str);
		i++;
	}
	printf("\n");
	return (0);
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