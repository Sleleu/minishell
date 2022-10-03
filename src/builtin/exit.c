/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 00:52:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/03 20:56:59 by rvrignon         ###   ########.fr       */
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

int	exit_error(char **cmd)
{
	int	i;

	i = 0;
	while (ft_strncmp(cmd[i], "exit", ft_strlen("exit")))
		i++;
	if (i != 0)
		return (0);
	while (cmd[i])
		i++;
	if (cmd[1] && exit_numeric_error(cmd[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		return (2); // exit et change le code
	}
	if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1); // exit pas, mais change le code
	}
	return (-1);
}

int	ft_exit(char **cmd)
{
	int	code;
	code = -1;
	code = exit_error(cmd);
	if (code != -1)
		return (code);
	if (cmd[1])
	{
		code = (ft_atoi(cmd[1]) % 256);
		if (code < 0)
			code = 256 + code;
	}
	return (code);
}

// ajout d'un exit meme si numeric error a faire