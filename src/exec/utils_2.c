/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 22:26:28 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/11 19:29:45 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	gotoparsecmd(t_data *data, int cmd)
{
	int	i;

	i = 0;
	while (data->parse[i].type != FINISH && data->parse[i].cmd != cmd)
		i++;
	return (i);
}

char	*setpath(char *cmd, char **envp)
{
	if (!cmd)
		return (NULL);
	else
	{
		if (!find_cmdpath(cmd, envp))
			return (cmd);
		else
			return (find_cmdpath(cmd, envp));
	}
	return (NULL);
}

int	is_path(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (av[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	print_both(t_data *data)
{
	t_parse	*parse;
	t_exec	*exec;
	int		i;

	parse = data->parse;
	exec = data->exec;
	i = -1;
	dprintf(2, "\nPARSING\n");
	while (parse[++i].type != FINISH)
	{
		dprintf(2, "%d\tType : %d | Cmd : %d | Content : %s\n",
			i, parse[i].type, parse[i].cmd, parse[i].str);
	}	
	i = -1;
	dprintf(2, "\nEXECUTING\n");
	while (++i < data->args)
	{
		dprintf(2, "%d Cmd : %d | Heredoc : %d\n",
			i, exec[i].cmd, exec[i].heredoc);
	}
	dprintf(2, "\n");
}

int	getwords(t_data *data, int cmdnb)
{
	int		i;
	int		words;
	t_parse	*parse;

	parse = data->parse;
	i = -1;
	words = 0;
	while (parse[++i].type != FINISH)
	{
		if (parse[i].type == WORD && parse[i].cmd == cmdnb)
			words++;
	}
	return (words);
}
