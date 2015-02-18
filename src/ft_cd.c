/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 15:52:58 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/18 17:08:05 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_update_env(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->env[i])
	{
		if (ft_strnstr(cmd->env[i], "PWD=", 4) != NULL)
			cmd->env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
		if (ft_strnstr(cmd->env[i], "OLDPWD=", 7) != NULL)
			cmd->env[i] = ft_strjoin("OLD", cmd->pwd);
		i++;
	}
}

void	ft_go_home(t_cmd *cmd)
{
	int i;

	i = 0;

	while (cmd->env[i])
	{
		if (ft_strnstr(cmd->env[i], "HOME=", 5) != NULL)
		{
			chdir(cmd->env[i] + 5);
		}
		if (ft_strnstr(cmd->env[i], "PWD=", 4) != NULL)
			cmd->env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
		if (ft_strnstr(cmd->env[i], "OLDPWD=", 7) != NULL)
		{
			ft_putendl("tatata");
			cmd->env[i] = ft_strjoin("OLD", cmd->pwd);
		}
		i++;
	}
}

void	ft_previous_dir(t_cmd *cmd)
{
	int i;

	i = 0;
	chdir(cmd->oldpwd + 7);
	while (cmd->env[i])
	{
		if (ft_strnstr(cmd->env[i], "PWD=", 4) != NULL)
			cmd->env[i] = ft_strjoin("PWD=", cmd->oldpwd + 7);
		if (ft_strnstr(cmd->env[i], "OLDPWD=", 7) != NULL)
			cmd->env[i] = ft_strjoin("OLD", cmd->pwd);
		i++;
	}
}

void	ft_cd_error(t_cmd *cmd)
{
	int i;

	i = ft_nb_tab(cmd->arg);

	if (i == 1 || (ft_strcmp(cmd->name, "cd") == 0))
		ft_go_home(cmd);
	else if (ft_strcmp(cmd->arg[1], "-") == 0)
		ft_previous_dir(cmd);
	else if (i != 2 && i != 0)
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(cmd->arg[1]);
	}
	else
	{
		ft_putstr(cmd->arg[1]);
		ft_putendl(": No such file of directory");
	}
}

int		ft_change_dir(t_cmd *cmd)
{
	int i;

	i = ft_nb_tab(cmd->arg);

	if (i > 2)
	{
		ft_putendl("cd: Too many arguments");
		return (1);
	}

	ft_tild(cmd, 1);

	if ((chdir(cmd->arg[1])) == 0)
		ft_update_env(cmd);
	else
		ft_cd_error(cmd);
	return (0);
}
