/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:34 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/14 20:01:08 by rbaum            ###   ########.fr       */
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

void	check_path(t_cmd *cmd)
{
	int i;
	int k;

	ft_putendl("chekc check");
	cmd->path = ft_strsplit(cmd->env[0] + 5, ':');
	ft_clear_tab(cmd->arg);
	cmd->arg = ft_strsplit(cmd->name, ' ');
	i = 0;
	while (cmd->path[i])
	{
		cmd->path[i] = ft_strjoin(cmd->path[i], "/");
		cmd->path[i] = ft_strjoin(cmd->path[i], cmd->arg[0]);
		if ((access(cmd->path[i], F_OK)) != -1)
		{
			ft_exec(cmd, i);
			k = 1;
		}
		i++;
	}
	if (k != 1)
		ft_error();
}

void	ft_gest_cmd(t_cmd *cmd)
{
	if (ft_strnstr(cmd->name, "exit", 4) != NULL)
		ft_exit(cmd);
	else if(ft_strnstr(cmd->name, "setenv", 6) != NULL)
		set_env(cmd);
	else if(ft_strnstr(cmd->name, "env", 3) != NULL)
		aff_env(cmd);
	else if (ft_strnstr(cmd->name, "unsetenv", 8) != NULL)
		ft_unsetenv(cmd);
	else if (ft_strnstr(cmd->name, "cd", 2) != NULL)
		ft_get_pwd(cmd);
	else if (cmd->name[0] == '\0')
		cmd->name = cmd->name;
	else
		check_path(cmd);
}

