/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:35:34 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/11 02:27:42 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_parameter(char *arg)
{
	int	i;

	i = 1;
	if (ft_strlen(arg) < 2)
		return (0);
	if (!ft_strncmp(arg, "-n", 2))
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				break ;
			i++;
		}
	}
	if (!arg[i])
		return (1);
	return (0);
}

int	ft_echo(char **arg)
{
	int	i;
	int	nl;

	nl = 1;
	if (is_parameter(arg[1]))
	{
		i = 2;
		nl = 0;
	}
	else
		i = 1;
	while (is_parameter(arg[i]))
		i++;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
