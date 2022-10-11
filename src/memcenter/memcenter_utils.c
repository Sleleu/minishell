/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcenter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:45:17 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 02:45:58 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*after_malloc(size_t size, void *adress, t_label label)
{
	t_data		*data;
	t_memcenter	*head;
	t_memcenter	*tmp;

	data = get_data();
	head = data->memcenter;
	while (head->next != NULL)
		head = head->next;
	tmp = (t_memcenter *)malloc(sizeof(t_memcenter));
	if (!tmp)
		return (NULL);
	if (adress)
		tmp->adress = adress;
	else
		tmp->adress = (void *)malloc(size * 1);
	if (!tmp->adress)
		tmp->adress = NULL;
	tmp->label = label;
	tmp->next = NULL;
	head->next = tmp;
	return (tmp->adress);
}
