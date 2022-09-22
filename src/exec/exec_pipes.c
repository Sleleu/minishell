/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:10 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/22 18:41:17 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_double(char **lol)
{
	int	i;

	i = 0;
	while (lol[i])
	{
		free(lol[i]);
		i++;
	}
	free(lol);
}

void	err_return(char **cmd)
{
	char	*err;
	int		i;

	if (!cmd)
		ft_putstr_fd("Command '' not found\n", 2);
	else
	{
		err = ft_strjoin(cmd[0], ": Command not found\n");
		ft_putstr_fd(err, 2);
		free(err);
		i = -1;
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
	}
	close_pipes(get_data());
}

// void	child_process(t_pipex *pipex)
// {
// 	if (handle_fd(pipex))
// 		execute(pipex->av[pipex->i], pipex->envp, pipex->fd);
// }

int	getcmdnb(t_parse *parse)
{
	int i;

	i = 0;
	while (parse[i].type != FINISH)
		i++;
	return (parse[i].cmd);
}

void	exec_pipes_process(t_data *data)
{
	t_parse *parse;

	parse = data->parse;
	print_both(data);
	(void)parse;
	
	// if (data->actual < data->args)
	// {
	// 	if (pipe(pipex->fd) == -1)
	// 		return ;
	// 	pipex->pid = fork();
	// 	if (pipex->pid < 0)
	// 		error();
	// 	if (pipex->pid == 0)
	// 		child_process(pipex);
	// 	if (pipex->pid > 0 && ((i < pipex->i && !pipex->outfile) || (pipex->outfile && i < pipex->i - 2)))
	// 	{	
	// 		if (pipex->heredoc && pipex->i == 2)
	// 			wait(0);
	// 		if (pipex->fd[1] > 0)
	// 			close(pipex->fd[1]);
	// 		if (pipex->oldfd > 0)
	// 			close(pipex->oldfd);
	// 		pipex->oldfd = pipex->fd[0];
	// 		pipex->i++;
	// 		process(pipex);
	// 	}
	// 	wait(0);
	// }
}

int	exec_pipes(t_data *data)
{
	// t_pipex *pipex;

	// pipex = data->pipex;
	// pipex = init_pipex();
	exec_pipes_process(data);
	(void)exec;
	// close(pipex->fd[0]);
	// close(pipex->fd[1]);
	// close(pipex->oldfd);
	return (0);
}
