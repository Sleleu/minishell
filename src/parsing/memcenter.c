/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcenter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:53:31 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/15 21:58:55 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data *get_data(void)
{
	static t_data data;

	return(&data);
}

void	*memflush(t_memcenter *head)
{
	t_memcenter *tmp;
	
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
	dprintf(2, "Free\nhead->adress %p\n", head->adress);
	free(adress);
	head->adress = NULL;
	return (NULL);
}

void	*first_malloc(size_t size, void *adress)
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
		head->adress = (void *)malloc(sizeof(void) * size);
	if (!head->adress)
		head->adress = NULL;
	head->next = NULL;
	head->hello = "Let's gooo";
	data->memcenter = head;
	return (head->adress);
}

void	*after_malloc(size_t size, void *adress)
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
		head->adress = (void *)malloc(sizeof(void) * size);
	if (!tmp->adress)
		tmp->adress = NULL;
	tmp->hello = "To be continued...";
	tmp->next = NULL;
	head->next = tmp;
	return (tmp->adress);
}

void	*memcenter(t_mem mem, size_t size, void *adress)
{
	t_data		*data;
	t_memcenter	*head;

	data = get_data();
	head = data->memcenter;
	if (mem == FLUSH)
		return (memflush(head));
	else if (mem == FREE)
		return (memfree(head, adress));
	else if (mem == MALLOC && head == NULL)
		return	(first_malloc(size, adress));
	else if (mem == MALLOC)
		return (after_malloc(size, adress));
	return (NULL);
}

/* USAGE MEMCENTER

-> test = malloc(sizeof(char *) * 6);
memcenter(MALLOC, sizeof(char *) * 6, NULL);

-> test = ft_split(line, ' ');
memcenter(MALLOC, 0, ft_split(line, ' '));

-> free(test);
memcenter(FREE, 0, test);

->free all
memcenter(FLUSH, 0, NULL);

*/