/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:30 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/15 19:49:05 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_exec(t_cmd *cmd, char *path)
{
	pid_t	pid;
	int		stat;

	cmd = cmd;
	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid > 0)
		waitpid(pid, &stat, 0);
	else
		execve(path, cmd->arg, cmd->env);
}

void	ft_prompt(t_cmd *cmd)
{
	int		ret;
	char	*line;

	ft_putstr("no_prompt>$ ");
	while ((ret = get_next_line(1, &line)) != 0)
	{
		cmd->name = ft_strdup(line);
		ft_get_right_cmd(cmd);
		ft_clear_tab(cmd->arg);
		cmd->arg = ft_strsplit(cmd->name, ' ');
		ft_get_pwd(cmd);
		ft_gest_cmd(cmd);
		free(line);
		ft_putstr("no_prompt>$ ");
	}
}
