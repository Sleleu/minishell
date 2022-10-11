/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcenter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:11:54 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 02:46:05 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* USAGE MEMCENTER

-> test = (t_list *)malloc(sizeof(t_list));
memcenter(MALLOC, sizeof(t_list *), NULL);

-> test = ft_split(line, ' ');
memcenter(MALLOC, 0, ft_split(line, ' '));

-> free(test);
memcenter(FREE, 0, test);

->free all
memcenter(PURGE, 0, NULL);

*/

void	*memcenter(t_mem mem, size_t size, void *adress, t_label label)
{
	t_data		*data;
	t_memcenter	*head;

	data = get_data();
	head = data->memcenter;
	if (mem == PURGE)
		return (mempurge(head));
	else if (mem == FREE)
		return (memfree(head, adress));
	else if (mem == FREE_WHERE)
		return (memfreewhere(head, label));
	else if (mem == MALLOC && head == NULL)
		return (first_malloc(size, adress, label));
	else if (mem == MALLOC)
		return (after_malloc(size, adress, label));
	return (NULL);
}

void	*mempurge(t_memcenter *head)
{
	t_memcenter	*tmp;

	if (!head)
		return (NULL);
	while (head->next != NULL)
	{
		tmp = head;
		free(tmp->adress);
		head = head->next;
		free(tmp);
	}
	free(head->adress);
	free(head);
	return (NULL);
}

void	*memfree(t_memcenter *head, void *adress)
{
	if (head->adress == adress)
	{	
		free(adress);
		head->adress = NULL;
	}
	while (head->adress != adress)
		head = head->next;
	free(adress);
	head->adress = NULL;
	return (NULL);
}

void	*memfreewhere(t_memcenter *head, t_label label)
{
	if (head->label == label)
	{	
		free(head->adress);
		head->adress = NULL;
	}
	while (head)
	{
		if (head->label == label)
		{
			free(head->adress);
			head->adress = NULL;
		}
		head = head->next;
	}
	return (NULL);
}

void	*first_malloc(size_t size, void *adress, t_label label)
{
	t_data		*data;
	t_memcenter	*head;

	data = get_data();
	head = data->memcenter;
	head = (t_memcenter *)malloc(sizeof(t_memcenter));
	if (!head)
		return (NULL);
	if (adress)
		head->adress = adress;
	else
		head->adress = (void *)malloc(size * 1);
	if (!head->adress)
		head->adress = NULL;
	head->next = NULL;
	head->label = label;
	data->memcenter = head;
	return (head->adress);
}
