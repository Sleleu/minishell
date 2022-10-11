/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:10:24 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 20:14:01 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_files	*getfiles(int file, int cmd, t_data *data)
{
	t_files	*dtab;
	t_parse	*parse;
	int		i;
	int		size;

	parse = data->parse;
	i = gotoparsecmd(data, cmd);
	size = 0;
	while (parse[i].type != FINISH && parse[i].cmd == cmd)
	{
		if (!file && parse[i].type == INF_CHEVRON)
			size++;
		else if (file
			&& (parse[i].type == SUP_CHEVRON || parse[i].type == D_SUP_CHEVRON))
			size++;
		i++;
	}
	if (!size)
		return (NULL);
	dtab = memcenter(MALLOC, sizeof(t_files) * (size + 1), NULL, EXEC);
	if (!dtab)
		return (NULL);
	dtab[size].token = FINISH;
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
	while (data->parse[i].type != FINISH && data->parse[i].cmd == cmd)
	{
		if (data->parse[i].type == INF_CHEVRON)
		{
			exec.infile[infile] = exec_file_process(data->parse[i + 1].str);
			infile++;
		}
		else if (data->parse[i].type == LIMITER)
			exec.heredoc++;
		else if (data->parse[i].type == SUP_CHEVRON
			|| data->parse[i].type == D_SUP_CHEVRON)
		{
			exec.outfile[outfile] = exec_file_process(data->parse[i + 1].str);
			outfile++;
		}
		i++;
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

pid_t	*getpidtab(t_data *data)
{
	pid_t	*pidtab;
	int		i;

	pidtab = memcenter(MALLOC, sizeof(pid_t *) * data->args + 1, NULL, DATA);
	if (!pidtab)
		return (0);
	i = -1;
	while (++i < data->args)
		pidtab[i] = 1;
	pidtab[i] = 0;
	return (pidtab);
}

void	process(t_data **data)
{	
	(*data)->args = getargsnb((*data)->parse);
	(*data)->pid = getpidtab((*data));
	if ((*data)->parse != NULL)
		(*data)->exec = setexec(*data);
	if (!(*data)->exec)
		return ;
	return (execution(*data));
}
