/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:05:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/12 15:11:25 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int _)
{
	(void)_;
	if (g_sigstatus.heredoc)
		exit(130);
	if (!g_sigstatus.process)
	{
		printf("\n");
		g_sigstatus.value = 0;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sigstatus.value = 1;
	}
	else
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
		g_sigstatus.process = 0;
	}
}

// void	ft_handler(int signum)
// {
// 	if (signum == SIGINT)
// 		printf("yo2"); // exit sur les process, pas sur le minishell
// 	else if (signum == SIGQUIT)
// 		printf("Quit (core dumped)\n"); // uniquement sur les process, 
// pas sur le minishell
// }

// void	sig_init(void)
// {
// 	signal(SIGINT, ft_handler);
// 	signal(SIGQUIT, ft_handler);
// }

//signal
// ctrl C devient le
// si que des quotes on tenter de lancer une commande
