/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcenter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 02:45:17 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 22:09:36 by sleleu           ###   ########.fr       */
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
	tmp = malloc(sizeof(t_memcenter));
	if (!tmp)
		return (NULL);
	if (adress)
		tmp->adress = adress;
	else
		tmp->adress = malloc(size);
	if (!tmp->adress)
		tmp->adress = NULL;
	tmp->label = label;
	tmp->next = NULL;
	head->next = tmp;
	return (tmp->adress);
}
