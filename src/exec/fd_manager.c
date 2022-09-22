/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:02:30 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/21 14:07:14 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	check_path(char **envp)
// {
// 	char	**paths;
// 	int		value;

// 	paths = find_path(envp);
// 	if (!paths)
// 	{	
// 		ft_printf("Env error\n");
// 		value = 0;
// 	}
// 	else
// 	{
// 		free_double(paths);
// 		value = 1;
// 	}
// 	return (value);
// }

// int	first_cmd(t_pipex *pipex)
// {
// 	int	filein;

// 	filein = open(pipex->av[1], O_RDONLY);
// 	if (filein == -1)
// 	{
// 		perror(pipex->av[1]);
// 		close_pipes(pipex->fd);
// 		return (0);
// 	}
// 	dup2(filein, STDIN_FILENO);
// 	dup2(pipex->fd[1], STDOUT_FILENO);
// 	close(pipex->fd[0]);
// 	return (1);
// }

// int	heredoc(t_pipex *pipex)
// {
// 	char	*line;

// 	ft_putstr_fd("> ", 2);
// 	line = get_next_line(0, pipex->av[2]);
// 	while (line)
// 	{
// 		write(pipex->fd[1], line, ft_strlen(line));
// 		free(line);
// 		ft_putstr_fd("> ", 2);
// 		line = get_next_line(0, pipex->av[2]);
// 	}
// 	close(pipex->fd[0]);
// 	return (0);
// }

// int	last_cmd(t_pipex *pipex)
// {
// 	int		fileout;
// 	char	**av;
// 	int		i;

// 	av = pipex->av;
// 	i = pipex->ac - 1;
// 	if (pipex->heredoc)
// 		fileout = open(av[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		fileout = open(av[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fileout == -1)
// 	{
// 		perror(pipex->av[pipex->ac - 1]);
// 		close_pipes(pipex->fd);
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(pipex->oldfd, STDIN_FILENO);
// 	dup2(fileout, STDOUT_FILENO);
// 	close(pipex->fd[1]);
// 	return (1);
// }

// int	handle_fd(t_pipex *pipex)
// {
// 	if (pipex->i == 2 && !pipex->heredoc)
// 		return (first_cmd(pipex));
// 	else if (pipex->i == 2 && pipex->heredoc)
// 		return (heredoc(pipex));
// 	else if (pipex->i == pipex->ac - 2)
// 		return (last_cmd(pipex));
// 	else
// 	{
// 		dup2(pipex->oldfd, STDIN_FILENO);
// 		dup2(pipex->fd[1], STDOUT_FILENO);
// 		close(pipex->fd[0]);
// 		return (1);
// 	}
// }
