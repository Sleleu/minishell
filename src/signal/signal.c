/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleleu <sleleu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:05:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/12 18:02:24 by sleleu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void			sig_handler2(int signum)
{
	(void)signum;
	printf("\n");
}

void	sig_handler(int signum)
{
	(void)signum;
	if (g_sigstatus.heredoc)
		exit(130);
	if (!g_sigstatus.process)
	{
		printf("\n");
		g_sigstatus.value = 0;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sigstatus.value = 1;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sigstatus.process = 0;
	}
}

void	sigquit_handler(int signum)
{
	(void)signum;
	printf("Quit (code dumped)\n");
	*g_sigstatus.code = 131;
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