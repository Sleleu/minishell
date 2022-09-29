/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 00:52:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/09/30 01:52:25 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long long int	ft_long_atoi(char *str)
{
	long long int		result;
	int					sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	exit_numeric_error(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str && str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (1);
		i++;
	}
	if (ft_strlen(str) > 11)
		return (1);
	if (ft_long_atoi(str) > 2147483647 || ft_long_atoi(str) < -2147483648)
		return (1);
	return (0);
}

int	exit_error(t_parse *parse)
{
	int	i;

	i = 0;
	while (ft_strncmp(parse[i].str, "exit", ft_strlen("exit")))
		i++;
	if (i != 0)
		return (0);
	while (parse[i].type != FINISH)
	{
		if (parse[i].type != WORD)
			break ;
		i++;
	}
	if (parse[1].str && exit_numeric_error(parse[1].str))
	{
		printf("minishell: exit: %s: numeric argument required\n", parse[1].str);
		return (2);
	}
	if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	return (-1);
}

int	ft_exit(t_parse *parse)
{
	int	code;

	code = -1;
	code = exit_error(parse);
	if (code != -1)
		return (code);
	if (parse[1].str)
	{
		code = (ft_atoi(parse[1].str) % 256);
		if (code < 0)
		{
			code = 256 + code;
			code = code * -1;
		}
	}
	return (-1);
}

// ajout d'un exit meme si numeric error a faire