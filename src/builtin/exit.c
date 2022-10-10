/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 00:52:14 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/10 23:05:44 by rvrignon         ###   ########.fr       */
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

int	exit_numeric_error(t_data **data, char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str && str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
		{
			(*data)->exit[0] = 1;
			(*data)->exit[1] = 1;
			return (-1);
		}
		i++;
	}
	if (ft_strlen(str) > 11 || ft_long_atoi(str) > 2147483647
			|| ft_long_atoi(str) < -2147483648)
	{
		(*data)->exit[0] = 1;
		(*data)->exit[1] = 1;
		return (-1);
	}
	return (0);
}

int	exit_error(t_data **data, char **cmd)
{
	int	i;

	i = 0;
	while (ft_strncmp(cmd[i], "exit", ft_strlen("exit")))
		i++;
	if (i != 0)
		return (0);
	while (cmd[i])
		i++;
	if (cmd[1] && exit_numeric_error(data, cmd[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		(*data)->exit[0] = 1;
		(*data)->exit[1] = 2;
		return (-1);
	}
	if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		(*data)->exit[1] = 1;
		return (-2);
	}
	return (-1);
}

void	ft_exit(t_data **data, char **cmd)
{
	int	code;
	code = -1;
	ft_putstr_fd("exit\n", 1);
	code = exit_error(data, cmd);
	if (code == -1)
		return ;
	if (cmd[1] && code != -2)
	{
		code = (ft_atoi(cmd[1]) % 256);
		if (code < 0)
			code = 256 + code;
		(*data)->exit[1] = code;
	}
	else
		(*data)->exit[1] = 0;
	if (code == -2)
		(*data)->exit[1] = 1;
	(*data)->exit[0] = 1;
	return ;
}

// ajout d'un exit meme si numeric error a faire