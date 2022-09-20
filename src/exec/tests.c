/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 19:11:15 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/20 19:31:50 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
parse[0].str = NULL
parse[0].type = Inf Chevron

parse[1].str = Makefile
parse[1].type = Word

parse[2].str = cat
parse[2].type = Word

parse[3].str = NULL
parse[3].type = PIPE

parse[4].str = ls
parse[4].type = WORD

parse[5].str = NULL
parse[5].type = SUP_CHEVRON

parse[6].str = outfile
parse[6].type = WORD
*/

t_parse	*simulate_parse(t_parse *parsing)
{
	parsing = get_data()->parse;
	parsing->str = "";
	parsing->type = WORD;
	return (parsing);
}