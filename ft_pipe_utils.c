/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:00:54 by dhyun             #+#    #+#             */
/*   Updated: 2022/09/19 15:37:14 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

char	*ft_strjoin_wc(char *s1, char *s2, char c)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	new = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = ft_calloc(len1 + len2 + 1 + 1, sizeof(char));
	if (new == 0)
		return (0);
	ft_memmove(new, s1, len1);
	new[len1] = c;
	ft_memmove(new + len1 + 1, s2, len2);
	return (new);
}

void	print_error(char *str, int code)
{
	if (errno == 0)
		ft_putstr_fd(str, 2);
	else
		perror(str);
	if (code != 0)
		exit(code);
}

int	check_access(char *tmp)
{
	int	ret;

	ret = access(tmp, X_OK);
	if (ret == 0)
	{
		free(tmp);
		return (ret);
	}
	return (1);
}

char	*sel_path(t_pipe_data *pipe_data, t_pipe_cmds *pipe_cmds)
{
	int		i;
	int		ret;
	char	*tmp;

	i = 0;
	ret = access(pipe_cmds->cmds, X_OK);
	if (ret == 0)
		return (pipe_cmds->cmds);
	else if (ret == -1 && errno == 13)
		print_error("access", 126);
	while (pipe_data->path[i] != 0)
	{
		tmp = ft_strjoin_wc(pipe_data->path[i], pipe_cmds->cmds, '/');
		ret = check_access(tmp);
		if (ret == 0)
			return (ft_strjoin_wc(pipe_data->path[i], pipe_cmds->cmds, '/'));
		else if (ret == -1 && errno == 13)
			print_error("access", 126);
		i++;
		free(tmp);
		tmp = 0;
	}
	return (0);
}
