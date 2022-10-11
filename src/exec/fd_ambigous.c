/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_ambigous.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 00:22:19 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 19:26:53 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check(char *first, char *second)
{
	if (!first || !second)
		return (1);
	if (ft_ultracmp(first, second))
		return (1);
	return (0);
}

static int	ambigous_infile(t_data *data, int cmd, int i)
{
	t_lexer	*ptr;
	int		index_cpy;
	char	*file;

	file = data->exec[cmd - 1].infile[i].file;
	ptr = data->lexer;
	index_cpy = i + 1;
	while (ptr->cmd != cmd)
		ptr = ptr->next;
	while (ptr && index_cpy)
	{
		if (ptr->type == INF_CHEVRON)
			index_cpy--;
		ptr = ptr->next;
	}
	if (ptr->content[0] != '$')
		return (0);
	if (check(file, ft_getenv(data->env, ptr->content + 1)))
	{
		printf("minishell: %s: ambiguous redirect\n", ptr->content);
		return (1);
	}
	return (0);
}

static int	ambigous_outfile(t_data *data, int cmd, int i)
{
	t_lexer	*ptr;
	int		index_cpy;
	char	*file;

	file = data->exec[cmd - 1].outfile[i].file;
	ptr = data->lexer;
	index_cpy = i + 1;
	while (ptr->cmd != cmd)
		ptr = ptr->next;
	while (ptr && index_cpy)
	{
		if (ptr->type == SUP_CHEVRON || ptr->type == D_SUP_CHEVRON)
			index_cpy--;
		ptr = ptr->next;
	}
	if (ptr->content[0] != '$')
		return (0);
	if (check(file, ft_getenv(data->env, ptr->content + 1)))
	{
		printf("minishell: %s: ambiguous redirect\n", ptr->content);
		return (1);
	}
	return (0);
}

int	ft_ambigous(t_data *data, int cmd, char c, int i)
{
	if (c == 'i')
		return (ambigous_infile(data, cmd, i));
	else if (c == 'o')
		return (ambigous_outfile(data, cmd, i));
	return (0);
}
