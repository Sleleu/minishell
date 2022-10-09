/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:02:30 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/09 22:53:22 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_fd(t_data *data, int cmd)
{
	if (!fd_infile(data, cmd))
		return (0);
	if (!fd_outfile(data, cmd))
		return (0);
	return (1);
}
