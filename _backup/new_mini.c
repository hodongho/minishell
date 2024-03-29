/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mini.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:54:54 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/28 15:56:37 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_argnode	*ft_new_argnode(char c)
{
	t_argnode	*new;

	new = ft_calloc(1, sizeof(t_argnode));
	if (!new)
		return (NULL);
	new->c = c;
	return (new);
}

void	ft_push(t_arglist	*arglist, char c)
{
	t_argnode	*tt;
	t_argnode	*new;

	new = ft_new_argnode(c);
	arglist->tail->prev->next = new;
	new->next = arglist->tail;
	new->prev = arglist->tail->prev;
	arglist->tail->prev = new;
	arglist->datasize++;
}

char	*ft_makeword(t_arglist	*arglist)
{
	char		*str;
	char		*st;
	t_argnode	*curr;
	t_argnode	*temp;

	if (arglist->datasize == 0)
		return (NULL);
	st = ft_calloc(arglist->datasize + 1, sizeof(char));
	str = st;
	curr = arglist->head->next;
	while (curr->next)
	{
		*str = curr->c;
		temp = curr;
		curr = curr->next;
		free(temp);
		arglist->datasize--;
		str++;
	}
	arglist->head->next = arglist->tail;
	arglist->tail->prev = arglist->head;
	return (st);
}

char	*ft_chgenv(char *st, t_par_mdata *par_mdata, int type)
{
	char		*key;
	int			i;
	t_envnode	*curr;
	char		*st_val;
	char		*str;

	i = 0;
	st++;
	if (ft_switch(*st) != 3)
	{
		ft_push(par_mdata->arglist, '$');
		return (st);
	}
	else
	{
		// if (*st == '?')
		while (ft_switch(st[i]) == 3)
		{
			if (st[i] == '$' || ft_isalnum(st[i]) == 0)
				break ;
			i++;
		}
		key = ft_calloc(i + 1, sizeof(char));
		ft_memmove(key, st, i);
		curr = par_mdata->envlist->head;
		while (curr->next->next)
		{
			curr = curr->next;
			if (ft_strcmp(key, curr->key) == 0)
			{
				st_val = curr->val;
				if (!st_val)
					break ;
				while (*st_val)
				{
					if (ft_isspace(*st_val) == 1 && type == 3)
					{
						str = ft_makeword(par_mdata->arglist);
						ft_pushcmd(par_mdata->cmdlist, str, type);
						while (*st_val && ft_isspace(*st_val) == 1)
							st_val++;
					}
					ft_push(par_mdata->arglist, *st_val);
					st_val++;
				}
				break ;
			}
		}
		free(key);
		st = st + i;
	}
	return (st);
}

void	ft_pushcmd(t_cmdlist *cmdlist, char *str, int type)
{
	t_cmdnode	*new;
	t_cmdnode	*prev;
	char		*new_str;

	if (type == 3 && str == 0)
		return ;
	new_str = str;
	if (str == 0)
		new_str = ft_calloc(1, sizeof(char));
	new = ft_calloc(1, sizeof(t_cmdnode));
	// if(!new)
	// 	return (NULL); print 함수 만들고 exit 쓰기
	new->str = new_str;
	prev = cmdlist->tail->prev;
	new->next = cmdlist->tail;
	new->prev = prev;
	prev->next = new;
	cmdlist->tail->prev = new;
	cmdlist->datasize++;
}







