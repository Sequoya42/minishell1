/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:34 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/14 23:49:45 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int		ft_error(void)
{
	ft_putendl("Unknown Error");
	return (1);
}

void	ft_get_right_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while ((*cmd->name == ' ' || *cmd->name == '\t'))
		cmd->name++;
	while (cmd->name[i])
	{
		while (cmd->name[i] == '\t')
			cmd->name[i] = ' ';
		i++;
	}
}

int		check_current(t_cmd *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	ft_tild(cmd, 0);
	while (cmd->env[i])
	{
		if (ft_strnstr(cmd->env[i], "PWD=", 4) != NULL)
			tmp = ft_strdup(cmd->env[i] + 4);
		i++;
	}
	tmp = ft_strjoin(tmp, "/");
	tmp = ft_strjoin(tmp, cmd->arg[0]);
	if ((access(tmp, F_OK)) != -1)
	{
		ft_exec(cmd, tmp);
		return (1);
	}
	return (0);
}

int		check_path(t_cmd *cmd)
{
	int i;
	
	cmd->path = ft_strsplit(cmd->env[0] + 5, ':');
	if ((check_current(cmd) == 1))
		return (1);
	i = 0;
	while (cmd->path[i])
	{
		cmd->path[i] = ft_strjoin(cmd->path[i], "/");
		cmd->path[i] = ft_strjoin(cmd->path[i], cmd->arg[0]);
		if ((access(cmd->path[i], F_OK)) != -1)
		{
			ft_exec(cmd, cmd->path[i]);
			return (1);
		}
		i++;
	}
	ft_putstr(cmd->arg[0]);
	ft_putendl(": Command not found.");
	return (0);
}

void	ft_gest_cmd(t_cmd *cmd)
{
	if (ft_strcmp(cmd->arg[0], "exit") == 0)
		ft_exit(cmd);
	else if(ft_strcmp(cmd->arg[0], "setenv") == 0)
		set_env(cmd);
	else if(ft_strcmp(cmd->arg[0], "env") == 0)
		aff_env(cmd);
	else if (ft_strcmp(cmd->arg[0], "unsetenv") == 0)
		ft_unsetenv(cmd);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		ft_change_dir(cmd);
	else if (cmd->arg[0] == '\0')
		cmd->name = cmd->name;
	else
		check_path(cmd);
}

