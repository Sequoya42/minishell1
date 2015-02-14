/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 15:52:58 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/14 20:00:30 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

char	*ft_get_back(char *str)
{
	int i;
	char *tmp;
	
	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	tmp = ft_strndup(str, i);
	return (tmp);
}

void	ft_update_env(t_cmd *cmd)
{
	int i;

	i = 0;
	ft_putendl("est");
	while (cmd->env[i])
	{
		if (ft_strnstr(cmd->env[i], "PWD=", 4) != NULL &&
			ft_strcmp(cmd->arg[1], "..") != 0)
		{
			cmd->env[i] = ft_strjoin(cmd->pwd, "/");
			cmd->env[i] = ft_strjoin(cmd->env[i], cmd->arg[1]);
		}
		else if (ft_strnstr(cmd->env[i], "PWD", 4) != NULL &&
				 ft_strcmp(cmd->arg[1], "..") == 0)
			cmd->env[i] = ft_get_back(cmd->env[i]);
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
			chdir(cmd->env[i] + 5);
		if (ft_strnstr(cmd->env[i], "PWD=", 4) != NULL)
		{
			cmd->env[i] = ft_strdup("PWD");
			cmd->env[i] = ft_strjoin(cmd->env[i], cmd->home + 4);
		}
		if (ft_strnstr(cmd->env[i], "OLDPWD=", 7) != NULL)
			cmd->env[i] = ft_strjoin("OLD", cmd->pwd);
		i++;
	}
}

void	ft_cd_error(t_cmd *cmd)
{
	int i;
	
	i = 0;
	i = ft_nb_tab(cmd->arg);
	ft_putendl(cmd->name);
	if (i == 1 || (ft_strcmp(cmd->name, "cd") == 0))
		ft_go_home(cmd);
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

void	ft_get_pwd(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->env[i])
	{
		if (ft_strnstr(cmd->env[i], "PWD=", 4) != NULL)
			cmd->pwd = ft_strdup(cmd->env[i]);
		if (ft_strnstr(cmd->env[i], "OLDPWD=", 7) != NULL)
			cmd->oldpwd = ft_strdup(cmd->env[i]);
		if (ft_strnstr(cmd->env[i], "HOME=", 5) != NULL)
			cmd->home = ft_strdup(cmd->env[i]);
		i++;
	}
	if (cmd->arg == NULL)
		ft_go_home(cmd);
	if ((chdir(cmd->arg[1])) == 0)
		ft_update_env(cmd);
 	else 
		ft_cd_error(cmd);
}
