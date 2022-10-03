/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:05:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/03 23:17:18 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handler(int signum)
{
	if (signum == SIGINT)
		printf("yo2"); // exit sur les process, pas sur le minishell
	else if (signum == SIGQUIT)
		printf("Quit (core dumped)\n"); // uniquement sur les process, pas sur le minishell
		
}

void	sig_init(void)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, ft_handler);
}

//signal
// ctrl C devient le
// si que des quotes on tenter de lancer une commande
