/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:07:13 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/04 20:30:19 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		islastfile(char **file, int i)
{
	if (!file)
		return (0);
	if (!file[i + 1])
		return (1);
	else
		return (0);
}

// int		islastinfile(t_data *data, char **infile, int cmd)
// {
// 	t_parse *parse;
// 	int		return_value;
// 	int		i;
	
// 	parse = data->parse;
// 	i = 0;
// 	return_value = 0;
// 	while (parse[i].cmd != cmd)
// 		i++;
// 	while (parse[i].type != FINISH && parse[i].cmd == cmd)
// 	{
// 		if (return_value != 0 && (parse[i].type == INFILE || parse[i].type == LIMITER))
// 			return (0);
// 		if (parse[i].type == INFILE && parse[i].str == infile)
// 			return_value++;
// 		i++;
// 	}
// 	// dprintf(2, "value %d", return_value);
// 	return (return_value);
// }