/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:07:13 by rvrignon          #+#    #+#             */
/*   Updated: 2022/10/10 22:57:33 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	islastinfile(t_data *data, char **file, int i, int cmd)
{
	t_parse	*parse;
	int		j;

	parse = data->parse;
	j = gotoparsecmd(data, cmd);
	while (parse[j].type != FINISH && parse[j].cmd == cmd)
	{
		if (parse[j].type == INFILE
			&& !ft_strncmp(parse[j].str, file[i], ft_strlen(file[i])))
		{
			j++;
			while (parse[j].type != FINISH && parse[j].cmd == cmd)
			{
				if (parse[j].type == INFILE || parse[j].type == LIMITER)
					return (0);
				j++;
			}
			return (1);
		}
		j++;
	}
	return (0);
}

int	islastoutfile(char **file, int i)
{
	if (!file)
		return (0);
	if (file[i + 1])
		return (0);
	return (1);
}

int	ambigous_infile(t_data *data, int cmd, int index)
{
	t_lexer	*ptr;

	ptr = data->lexer;
	while (ptr)
	{
		if (ptr->type == INF_CHEVRON && ptr->next->content[0] == '$')
			break ;
		ptr = ptr->next;
	}
	if (data->exec[cmd - 1].infile[index][0] == '\0')
	{
		printf("minishell: %s: ambiguous redirect\n", ptr->next->content);
		return (1);
	}
	return (0);
}

int	ft_ambigous(t_data *data, int cmd, char c, int index)
{
	t_lexer	*ptr;

	ptr = data->lexer;
	if (c == 'i')
		return (ambigous_infile(data, cmd, index));
	else if (c == 'o')
	{
		while (ptr)
		{
			if ((ptr->type == SUP_CHEVRON || ptr->type == D_SUP_CHEVRON)
				&& ptr->next->content[0] == '$')
				break ;
			ptr = ptr->next;
		}
		if (data->exec[cmd - 1].outfile[index][0] == '\0')
		{
			printf("minishell: %s: ambiguous redirect\n", ptr->next->content);
			return (1);
		}
	}
	return (0);
}

int	trybuiltin(t_data *data, char **cmd)
{
	int	return_value;

	return_value = -1;
	if (!ft_ultracmp(cmd[0], "cd"))
		return_value = ft_cd(cmd, data->env);
	else if (!ft_ultracmp(cmd[0], "echo"))
		return_value = ft_echo(cmd);
	else if (!ft_ultracmp(cmd[0], "env"))
		return_value = ft_env(data->env);
	else if (!ft_ultracmp(cmd[0], "export"))
		return_value = ft_export(&data, cmd);
	else if (!ft_ultracmp(cmd[0], "exit"))
	{
		return_value = 0;
		ft_exit(&data, cmd);
	}
	else if (!ft_ultracmp(cmd[0], "pwd"))
		return_value = ft_pwd();
	else if (!ft_ultracmp(cmd[0], "unset"))
		return_value = ft_unset(&data, cmd);
	return (return_value);
}
