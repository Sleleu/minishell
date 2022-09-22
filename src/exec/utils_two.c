/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:07:13 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/22 18:33:15 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// char *find_infile(int pipe)
// {
// 	int		i;
// 	t_parse *parse;
	
// 	parse = get_data()->parse;
// 	i = 0;
// 	while (pipe && parse[i].type != FINISH)
// 	{
// 		if (parse[i].type == PIPE)
// 			pipe--;
// 		i++;
// 	}
// 	while (parse[i].type != PIPE && parse[i].type != FINISH && parse[i].type != INF_CHEVRON)
// 		i++;
// 	if (parse[i].type == INF_CHEVRON)
// 		return (memcenter(MALLOC, 0, ft_strjoin(parse[i + 1].str, "\0"), EXEC));
// 	return (NULL);
// }

// char *find_outfile(int pipe)
// {
// 	int		i;
// 	t_parse *parse;
	
// 	parse = get_data()->parse;
// 	i = 0;
// 	while (pipe && parse[i].type != FINISH)
// 	{
// 		if (parse[i].type == PIPE)
// 			pipe--;
// 		i++;
// 	}
// 	while (parse[i].type != PIPE && parse[i].type != FINISH && parse[i].type != SUP_CHEVRON)
// 		i++;
// 	if (parse[i].type == SUP_CHEVRON)
// 		return (memcenter(MALLOC, 0, ft_strjoin(parse[i + 1].str, "\0"), EXEC));
// 	return (NULL);
// }

// char *find_word(int pipe, int word)
// {
// 	int		i;
// 	t_parse *parse;
	
// 	parse = get_data()->parse;
// 	i = 0;
// 	while (pipe && parse[i].type != FINISH)
// 	{
// 		if (parse[i].type == PIPE)
// 			pipe--;
// 		i++;
// 	}
// 	while (parse[i].type != FINISH && parse[i].type != PIPE && word)
// 	{
// 		if (parse[i].type == WORD && (parse[i - 1].type != INF_CHEVRON || parse[i - 1].type != SUP_CHEVRON))
// 			word--;
// 		i++;
// 	}
// 	return (parse[i].str);
// }

// int	is_heredoc(int pipe)
// {
// 	int i;
// 	int heredoc;
// 	t_parse *parse;

// 	parse = get_data()->parse;
// 	i = 0;
// 	while (pipe && parse[i].type != FINISH)
// 	{
// 		if (parse[i].type == PIPE)
// 			pipe--;
// 		i++;
// 	}
// 	heredoc = 0;
// 	while (parse[i].type != PIPE && parse[i].type != FINISH)
// 	{
// 		if (parse[i].type == D_INF_CHEVRON)
// 			heredoc++;
// 		i++;
// 	}
// 	return (heredoc);
// }

// t_exec	*set_exec(t_data *data)
// {
// 	t_exec	*exec;
// 	int		i;
// 	int		pipe;
	
// 	i = -1;
// 	pipe = 0;
// 	while (data->parse[++i].type != FINISH)
// 	{
// 		if (data->parse[i].type == PIPE)
// 			pipe++;
// 	}
// 	exec = get_data()->exec;
// 	exec = (t_exec *)memcenter(MALLOC, sizeof(t_exec) * (pipe + 2), NULL, EXEC);
// 	if (!exec)
// 		return (0);
// 	i = 0;
// 	while (i < pipe + 1)
// 	{
// 		exec[i].status = 1;
// 		exec[i].infile = find_infile(i);
// 		exec[i].outfile = find_outfile(i);
// 		exec[i].heredoc = is_heredoc(i);
// 		exec[i].cmd = find_word(i, 1);
// 		exec[i].opt = find_word(i, 2);
// 		i++;
// 	}
// 	exec[i].status = 0;
// 	return (exec);
// }

void	close_pipes(t_data *data)
{
	if (data->fd[0] > 0)
		close(data->fd[0]);
	if (data->fd[1] > 0)
		close(data->fd[1]);
	if (data->oldfd > 0)
		close(data->oldfd);
}

void	error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	print(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}
