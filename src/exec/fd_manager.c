/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:02:30 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/26 14:35:31 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token_type get_outfile_type(t_data *data, int cmd)
{
	t_parse *parse;
	int		i;

	parse = data->parse;
	i = -1;
	while (parse[++i].type != FINISH)
	{
		if (parse[i].cmd == cmd && (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T))
			return (parse[i].type);
	}
	return (FINISH);
}

int		handle_infile(t_data *data, int cmd)
{
	int filein; 
	
	filein = open(data->exec[cmd - 1].infile, O_RDONLY, 0644);
	if (filein < 0)
	{
		perror(data->exec[cmd - 1].infile);
		// close_pipes(data->fd);
		exit(EXIT_FAILURE);
	}
	dup2(filein, STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]); 
	return (1);
}

int		handle_outfile(t_data *data, int cmd)
{
	int fileout;
	
	if (get_outfile_type(data, cmd) == OUTFILE_T)
		fileout = open(data->exec[cmd - 1].outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (get_outfile_type(data, cmd) == OUTFILE_A)
		fileout = open(data->exec[cmd - 1].outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fileout < 0)
	{
		perror(data->exec[cmd - 1].outfile);
		// close_pipes(data->fd);
		exit(EXIT_FAILURE);
	}
	dup2(data->oldfd, STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(data->fd[1]);
	return (1); 
}

int		handle_fd(t_data *data, int cmd)
{
	// INFILE
	if (data->exec[cmd - 1].infile)
	{
		if (!handle_infile(data, cmd))
			return (0);
	}
	else
	{
		if (cmd == 1)
			dup2(data->fd[0], STDIN_FILENO);
		else
			dup2(data->oldfd, STDIN_FILENO);
	}
	
	// OUTFILE
	if (data->exec[cmd - 1].outfile)
	{		
		if (!handle_outfile(data, cmd))
			return (0);
	}
	else if (cmd < data->args)
		dup2(data->fd[1], STDOUT_FILENO);
	
	// dprintf(2, "--------- CMD %d ----------\n", cmd);
	// dprintf(2, "STDIN = %d\nSTDOUT = %d\nFD[0] = %d\nFD[1] = %d\n", STDIN_FILENO, STDOUT_FILENO, data->fd[0], data->fd[1]);
	// dprintf(2, "---------------------------\n\n");
	return (1);
}

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
