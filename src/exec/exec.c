/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:10:24 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/04 15:36:39 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_both(t_data *data)
{
	t_parse *parse;
	t_exec	*exec;
	int	i;

	parse = data->parse;
	exec = data->exec;
	i = -1;
	dprintf(2, "PARSING\n");
	while (parse[++i].type != FINISH)
		dprintf(2, "%d\tType : %d | Cmd : %d | Content : %s\n", i, parse[i].type, parse[i].cmd, parse[i].str);
	
	i = -1;
	dprintf(2, "\nEXECUTING\n");
	while (++i < data->args)
	{
		dprintf(2, "%d Cmd : %d | Heredoc : %d\n", i, exec[i].cmd, exec[i].heredoc);
	}
}

char **getfiles(int file, int cmd, t_data *data)
{
	char	**dtab;
	t_parse *parse;
	int		i;
	int		size;

	parse = data->parse;
	i = 0;
	while (parse[i].cmd != cmd)
		i++;
	size = 0;
	while (parse[i].type != FINISH && parse[i].cmd == cmd)
	{
		if (!file && parse[i].type == INFILE)
			size++;
		else if (file && (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T))
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

static t_exec	*setexec(t_data *data)
{
	int		i;
	int		infile;
	int		outfile;
	int		cmd;
	t_exec	*exec;
	t_parse *parse;

	exec = data->exec;
	parse = data->parse;
	exec = memcenter(MALLOC, sizeof(t_exec) * data->args + 1, NULL, EXEC);
	if (!exec)
		return (NULL);
	i = 0;
	cmd = 1;
	while (cmd <= data->args)
	{
		exec[cmd - 1].heredoc = 0;
		exec[cmd - 1].infile = getfiles(0, cmd, data);
		exec[cmd - 1].outfile = getfiles(1, cmd, data);
		exec[cmd - 1].cmd = cmd;
		infile = 0;
		outfile = 0;
		while (parse[i].type != FINISH && parse[i].cmd == cmd)
		{
			if (parse[i].type == INFILE)
			{
				exec[cmd - 1].infile[infile] = parse[i].str;
				infile++;
			}
			else if (parse[i].type == LIMITER)
				exec[cmd - 1].heredoc++;
			else if (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T)
			{
				exec[cmd - 1].outfile[outfile] = parse[i].str;
				outfile++;
			}
			i++;
		}
		cmd += 1;
	}
	return (exec);
}

int		process(t_data **data)
{	
	(*data)->args = getargsnb((*data)->parse);
	if ((*data)->parse != NULL)
		(*data)->exec = setexec(*data);
	if (!(*data)->exec)
		return (0);
	return (execution(*data));
}
