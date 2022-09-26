/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:10:24 by rvrignon          #+#    #+#             */
/*   Updated: 2022/09/26 13:00:44 by rvrignon         ###   ########.fr       */
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
		dprintf(2, "%d Cmd : %d | Infile : %s | Outfile : %s\n", i, exec[i].cmd, exec[i].infile, exec[i].outfile);
}

int		getargsnb(t_parse *parse)
{
	int i;

	i = 0;
	if (!parse)
		return (0);
	while (parse[i].type != FINISH)
		i++;
	return (parse[i - 1].cmd);
}

static t_exec	*setexec(t_data *data)
{
	int		i;
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
	// dprintf(2, "\nData args : %d\n", data->args);
	while (cmd <= data->args)
	{
		// dprintf(2, "\nCmd = %d || Parse cmd : %d\n", cmd, parse[i].cmd);
		exec[cmd - 1].infile = NULL;
		exec[cmd - 1].outfile = NULL;
		exec[cmd - 1].cmd = cmd;
		while (parse[i].type != FINISH && parse[i].cmd == cmd)
		{
			// dprintf(2, "%d\n", i);
			if (parse[i].type == INFILE || parse[i].type == LIMITER)
			{
				// dprintf(2, "True\n");
				exec[cmd - 1].infile = parse[i].str;
			}
			if (parse[i].type == OUTFILE_A || parse[i].type == OUTFILE_T)
			{
				// dprintf(2, "True\n");
				exec[cmd - 1].outfile = parse[i].str;
			}
			i++;
		}
		cmd += 1;
	}
	return (exec);
}

int		process(t_data **data)
{
	int			return_value;
	
	(*data)->args = getargsnb((*data)->parse);
	return_value = builtin(data);
	if (return_value != 6)
		return (return_value);
	if ((*data)->parse != NULL)
		(*data)->exec = setexec(*data);
	if (!(*data)->exec)
		return (0);
	execution(*data);
	return (1);
}
