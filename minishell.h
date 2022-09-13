/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:29:15 by nhwang            #+#    #+#             */
/*   Updated: 2022/09/13 12:06:58 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

typedef struct s_argnode
{
	struct s_argnode	*next;
	struct s_argnode	*prev;///
	char			c;
} t_argnode ;

typedef struct s_arglist
{
	t_argnode	*head; /// 초초기화// NULL
	t_argnode	*tail; // 초기화 //NULL
	int			datasize; //""
} t_arglist ;

typedef struct s_envnode
{
	struct s_envnode	*next;
	struct s_envnode	*prev;
	char				*key;
	char				*val;
} t_envnode ;

typedef struct s_envlist
{
	t_envnode	*head; /// 초초기화// NULL
	t_envnode	*tail; // 초기화 //NULL
	int		datasize; //""
} t_envlist ;

typedef struct s_cmdnode
{
	struct s_arglist	*next;
	struct s_arglist	*prev;
	char				*str;
} t_cmdnode ;

typedef struct s_cmdlist
{
	t_cmdnode	*head; /// 초초기화// NULL
	t_cmdnode	*tail; // 초기화 //NULL
	int			datasize; //""
} t_cmdlist ;

typedef struct s_par_mdata
{
	t_cmdlist	*

} t_par_mdata;

t_argnode	*ft_new_argnode(char c);
int			ft_switch(char c);
void		ft_removeq2(char *str, char **strarr, int len, t_arglist *arglist, t_envlist *s_envlist);
void 		ft_set_env(t_envlist *envlist, char **env);
t_envnode	*ft_newenv(void);
void 		ft_envinit(t_envlist *envlist);
