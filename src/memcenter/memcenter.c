/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcenter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 15:11:54 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/20 15:27:28 by rvrignon         ###   ########.fr       */
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

void	*memcenter(t_mem mem, size_t size, void *adress, char *label)
{
	t_data		*data;
	t_memcenter	*head;

	data = get_data();
	head = data->memcenter;
	if (mem == PURGE)
		return (mempurge(head));
	else if (mem == FREE)
		return (memfree(head, adress));
	else if (mem == MALLOC && head == NULL)
		return	(first_malloc(size, adress, label));
	else if (mem == MALLOC)
		return (after_malloc(size, adress, label));
	return (NULL);
}

void	*mempurge(t_memcenter *head)
{
	t_memcenter *tmp;
	
	if (!head)
		return (NULL);
	// dprintf(2, "--- PURGE ---\n");
	while (head->next != NULL)
	{
		// dprintf(2, "%s\n", head->label);
		tmp = head;
		free(tmp->adress);
		head = head->next;
		free(tmp);
	}
	// dprintf(2, "%s\n", head->label);
	// dprintf(2, "--------------\n\n");
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
	// dprintf(2, "Free\nhead->adress %p\n", head->adress);
	free(adress);
	head->adress = NULL;
	return (NULL);
}

void	*first_malloc(size_t size, void *adress, char *label)
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

void	*after_malloc(size_t size, void *adress, char *label)
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