/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:55:32 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/30 14:10:22 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(t_cmdlist *cmdlist)
{
	t_cmdnode	*arg;

	arg = cmdlist->head->next;
	while (arg->next)
	{
		if (ft_strcmp(arg->str, "|") == 0 && arg->p_type == 3)
			return (1);
		arg = arg->next;
	}
	return (0);
}

int	check_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "unset") == 0)
		return (1);
	return (0);
}

int	check_cmds(t_cmdlist *cmdlist)
{
	if (check_pipe(cmdlist) == 1)
		return (1);
	if (check_built_in(cmdlist->head->next->str) == 1)
		return (2);
	return (0);
}

void	ft_exec(t_cmdlist *cmdlist, t_envlist *envlist)
{
	int	ret;
	int	origin_in;
	int	origin_out;
	int redir;
	t_cmdnode *curr;


	ret = check_cmds(cmdlist);
	curr = cmdlist->head->next;
	while(curr->next)
	{
		redir = ft_is_redir(curr->str);
		if (redir != 0)
			break ;
		curr = curr->next;
	}
	if (redir && ret != 1)
	{
		origin_in = dup(STDIN_FILENO);
		origin_out = dup(STDOUT_FILENO);
		if (origin_in == -1 || origin_out == -1)
			exit(1);
		if (ft_redir(cmdlist) == -1)
			return ;
	}

	if (cmdlist->datasize != 0)
	{
		if (ret != 2)
			ft_exec_n_built_in(cmdlist, envlist);
		else
			ft_exec_built_in(cmdlist, envlist, 2);
	}


	if (redir && ret != 1)
	{
		if (dup2(origin_in, STDIN_FILENO) == -1)
			exit(1);
		if (dup2(origin_out, STDOUT_FILENO) == -1)
			exit(1);
		close(origin_in);
		close(origin_out);
	}

}
