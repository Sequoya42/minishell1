/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:34 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/18 19:18:43 by rbaum            ###   ########.fr       */
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

int		check_current(t_cmd *cmd, int k)
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
	tmp = ft_strjoin(tmp, cmd->arg[k]);
	if ((access(tmp, F_OK)) != -1)
	{
		ft_exec(cmd, tmp);
		return (1);
	}
	if ((access(cmd->arg[k], F_OK)) != -1)
	{
		ft_exec(cmd, cmd->arg[k]);
		return (1);
	}
	return (0);
}

int		check_path(t_cmd *cmd)
{
	int i;

	i = 0;
	ft_get_pwd(cmd);
	if ((check_current(cmd, 0) == 1))
		return (1);
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

void	ft_create_env(t_cmd *cmd)
{
	ft_putendl("Var PATH is set");
	cmd->env[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:\
/bin:/usr/sbin:/sbin:/opt/X11/bin:/usr/texbin:\
/nfs/zfs-student-5/users/2014_paris/rbaum/.brew/bin");
	cmd->env[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	cmd->env[2] = ft_strjoin("OLD=", cmd->env[1]);
}

void	ft_gest_cmd(t_cmd *cmd)
{

	if (ft_strcmp(cmd->arg[0], "exit") == 0)
		ft_exit(cmd);
	else if (ft_strcmp(cmd->arg[0], "setenv") == 0)
		set_env(cmd);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		aff_env(cmd);
	else if (ft_strcmp(cmd->arg[0], "unsetenv") == 0)
		ft_unsetenv(cmd);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		ft_change_dir(cmd);
	else if (cmd->arg[0] == '\0')
		cmd->name = cmd->name;
	else if (ft_strcmp(cmd->arg[0], "set_path") == 0)
		ft_create_env(cmd);
	else
		check_path(cmd);
}
