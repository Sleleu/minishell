/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:35:34 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/03 19:38:39 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(char **arg)
{
	int	i;
	int	nl;

	nl = 1;
	if (!ft_strncmp(arg[1], "-n", ft_strlen(arg[1])))
	{
		i = 2;
		nl = 0;
	}
	else
		i = 1;
	while(arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");	
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