/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:10:24 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/09 22:49:03 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**getfiles(int file, int cmd, t_data *data)
{
	char	**dtab;
	t_parse	*parse;
	int		i;
	int		size;

	parse = data->parse;
	i = gotoparsecmd(data, cmd);
	size = 0;
	while (parse[i].type != FINISH && parse[i].cmd == cmd)
	{
		if (!file && parse[i].type == INFILE)
			size++;
		else if (file
			&& (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T))
			size++;
		i++;
	}
	if (!size)
		return (NULL);
	dtab = memcenter(MALLOC, sizeof(char *) * (size + 1), NULL, EXEC);
	if (!dtab)
		return (NULL);
	dtab[size] = NULL;
	return (dtab);
}

t_exec	exec_finish(t_exec exec, t_data *data, int cmd)
{
	int	i;
	int	infile;
	int	outfile;

	i = gotoparsecmd(data, cmd);
	infile = 0;
	outfile = 0;
	while (data->parse[i++].cmd == cmd)
	{
		if (data->parse[i].type == INFILE)
		{
			exec.infile[infile] = data->parse[i].str;
			infile++;
		}
		else if (data->parse[i].type == LIMITER)
			exec.heredoc++;
		else if (data->parse[i].type == OUTFILE_A
			|| data->parse[i].type == OUTFILE_T)
		{
			exec.outfile[outfile] = data->parse[i].str;
			outfile++;
		}
	}
	return (exec);
}

static t_exec	*setexec(t_data *data)
{
	int		cmd;
	t_exec	*exec;

	exec = data->exec;
	exec = memcenter(MALLOC, sizeof(t_exec) * data->args + 1, NULL, EXEC);
	if (!exec)
		return (NULL);
	cmd = 0;
	while (++cmd <= data->args)
	{
		exec[cmd - 1].heredoc = 0;
		exec[cmd - 1].hfd = -1;
		exec[cmd - 1].infile = getfiles(0, cmd, data);
		exec[cmd - 1].outfile = getfiles(1, cmd, data);
		exec[cmd - 1].cmd = cmd;
		exec[cmd - 1] = exec_finish(exec[cmd - 1], data, cmd);
	}
	return (exec);
}

int	process(t_data **data)
{	
	(*data)->args = getargsnb((*data)->parse);
	if ((*data)->parse != NULL)
		(*data)->exec = setexec(*data);
	if (!(*data)->exec)
		return (0);
	return (execution(*data));
}
