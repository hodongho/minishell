/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhwang <nhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:59:47 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/30 18:37:53 by nhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_w_args(t_cmdnode *arg, t_envlist *envlist,
			char *home, char *old_pwd)
{
	char	*path;

	if (*arg->str == 0)
		path = ft_strdup(old_pwd);
	else if (arg->str[0] == '~')
		path = ft_strjoin(home, &arg->str[1]);
	else if (!ft_strcmp(arg->str, "-"))
	{
		path = find_val(envlist, "OLDPWD");
		if (path == 0)
		{
			print_error("cd: OLDPWD not set\n", 1);
			return (0);
		}
		else
			path = ft_strdup(path);
	}
	else
		path = ft_strdup(arg->str);
	return (path);
}

char	*set_cd_path(t_cmdlist *cmdlist, t_envlist *envlist, char *old_pwd)
{
	t_cmdnode	*arg;
	char		*home;
	char		*path;

	path = 0;
	arg = cmdlist->head->next->next;
	home = find_val(envlist, "HOME");
	if (home == 0 && cmdlist->datasize == 1)
	{
		print_error("cd: HOME not set\n", 1);
		return (0);
	}
	else if (home != 0)
		path = ft_strdup(home);
	if (cmdlist->datasize > 1)
	{
		if (path)
			free(path);
		path = cd_w_args(arg, envlist, home, old_pwd);
	}
	return (path);
}

void	ft_cd_set_env(t_envlist *envlist, char *old_pwd)
{
	char	*path;

	change_val(envlist, "OLDPWD", old_pwd);
	path = getcwd(0, 0);
	if (path == 0)
	{
		print_error("getcwd", 1);
		exit(1);
	}
	change_val(envlist, "PWD", path);
	g_data.exit_code = 0;
}

char	*set_old_pwd(t_envlist *envlist)
{
	char	*old_pwd;

	old_pwd = find_val(envlist, "PWD");
	if (old_pwd != 0)
		old_pwd = ft_strdup(old_pwd);
	else
	{
		old_pwd = getcwd(0, 0);

		// 현재 디렉토리가 없는 경우 getcwd가 Null을 리턴, oldpwd에 Null 할당하여 strjoin() 시 join 안됨
		// if (old_pwd == 0)
		// 	old_pwd = ft_strdup("");

		if (old_pwd == 0 && errno != 2)
		{
			print_error("getcwd", 1);
			exit(1);
		}
	}
	return (old_pwd);
}

void	ft_cd(t_cmdlist *cmdlist, t_envlist *envlist)
{
	char		*old_pwd;
	char		*path;

	old_pwd = set_old_pwd(envlist);
	path = set_cd_path(cmdlist, envlist, old_pwd);
	printf("old_pwd : %s, path : %s\n", old_pwd, path);
	if (path == 0)
	{
		free(old_pwd);
		return ;
	}
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		print_error("", 1);
		free(path);
		free(old_pwd);
		return ;
	}
	else if (cmdlist->head->next->next->str != 0
		&& !ft_strcmp(cmdlist->head->next->next->str, "-"))
		printf("%s\n", path);
	free(path);
	ft_cd_set_env(envlist, old_pwd);
}
