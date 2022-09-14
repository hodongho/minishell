/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:56:13 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/14 12:46:16 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chk_option(char *str)
{
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (1);
		str++;
	}
	return (0);
}

int	ft_echo(t_cmdlist *cmdlist, t_envlist *envlist)
{
	t_cmdnode	*arg;
	int			n_opt;

	arg = cmdlist->head->next->next;
	n_opt = 0;
	while (arg->next && *arg->str == '-')
	{
		if (chk_option(arg->str) == 1)
			break ;
		n_opt++;
		arg = arg->next;
	}
	while (arg->next)
	{
		printf("%s", arg->str);
		arg = arg->next;
		if (arg->next)
			printf(" ");
	}
	printf("$");
	if (n_opt == 0)
		printf("\n");
	return (0);
}
