/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhyun <dhyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:11:58 by dhyun             #+#    #+#             */
/*   Updated: 2022/07/18 12:23:48 by dhyun            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *data, t_cmd *cmds, int argc, char *argv[])
{
	data->infile = open(argv[1], O_RDONLY);
	if (data->infile == -1)
		print_error("open", 0);
	data->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->outfile == -1)
		print_error("open", 1);
	data->tmp = 0;
	data->path = 0;
	data->env = 0;
	data->pid = ft_calloc(argc - 2, sizeof(pid_t));
	if (data->pid == 0)
		print_error("calloc", 1);
	data->cmds = cmds;
}

void	init_cmds(t_cmd *cmds)
{
	cmds->cmds = 0;
	cmds->s_cmds = 0;
	cmds->p_cmds = 0;
	cmds->next = 0;
}

void	init_opt(t_opt *opt)
{
	opt->start = 0;
	opt->end = 0;
	opt->len = 0;
	opt->bs = 0;
}

void	init(t_data *data, t_cmd *cmds, int argc, char *argv[])
{
	init_data(data, cmds, argc, argv);
	init_cmds(cmds);
}