/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:05:29 by sleleu            #+#    #+#             */
/*   Updated: 2022/10/13 16:34:08 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler2(int signum)
{
	(void)signum;
	printf("\n");
}

void	sig_handler(int signum)
{
	(void)signum;
	*g_sigstatus.code = 130;
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
	if (!g_sigstatus.heredoc)
	{
		printf("Quit (code dumped)\n");
		*g_sigstatus.code = 131;
	}
}

void	sig_init(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
