 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 19:39:12 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/18 19:25:11 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

char		**pre_aff(t_cmd *cmd)
{
	int		i;
	int		k;
	char	**tmp;

	i = 0;
	k = 0;
	while (cmd->env[i])
	{
		if (cmd->env[i][0] == '\0')
			k++;
		i++;
	}
	if ((tmp = malloc(sizeof(char*) * (i - k) + 1)) == NULL)
		(ft_error());
	return (tmp);
}

int		ft_merdouille(t_cmd *cmd)
{
	int i;

    i = 0;
    ft_get_pwd(cmd);
    if ((check_current(cmd, 1) == 1))
        return (1);
    while (cmd->path[i])
    {
        cmd->path[i] = ft_strjoin(cmd->path[i], "/");
        cmd->path[i] = ft_strjoin(cmd->path[i], cmd->arg[1]);
        if ((access(cmd->path[i], F_OK)) != -1)
        {
            ft_exec(cmd, cmd->path[i]);
            return (1);
        }
        i++;
    }
	i = 0;
	while (cmd->arg[1][i])
	{
		if (cmd->arg[1][i] == '=')
		{
			//GEREZ CA
		}
		i++;
	}
	ft_putstr(cmd->arg[0]);
	ft_putstr(": ");
    ft_putstr(cmd->arg[1]);
    ft_putendl(": No such file or directory");
    return (0);
}

int			aff_env(t_cmd *cmd)
{
	int		i;
	int		k;
	char	**tmp;

	i = 0;
	k = 0;
	if (ft_nb_tab(cmd->arg) > 1)
		return (ft_merdouille(cmd));
	tmp = pre_aff(cmd);
	while (cmd->env[i])
	{
		while (cmd->env[i][0] == '\0' && cmd->env[i + 1])
			i += 1;
		if (cmd->env[i] && cmd->env[i][0] != '\0')
			ft_putendl(tmp[k++] = cmd->env[i]);
		i++;
	}
	cmd->env = tmp;
	return (0);
}

int			check_env(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = ft_nb_tab(cmd->arg);
	if (i == 1)
		return (aff_env(cmd));
	i = 0;
	while (cmd->arg[1][i])
	{
		if (cmd->arg[1][i++] == '=')
		{
			ft_putendl("setenv: Syntax Error");
			return (1);
		}
	}
	i = ft_nb_tab(cmd->arg);
	if (i > 3)
		ft_putendl("setenv: too many arguments.");
	i = 0;
	while (cmd->env[i])
	{
		tmp = ft_split_equ(cmd, i);
		if (ft_strcmp(tmp, cmd->arg[1]) == 0)
		{
			cmd->env[i] = ft_strjoin(cmd->arg[1], "=");
			if (cmd->arg[2])
				cmd->env[i] = ft_strjoin(cmd->env[i], cmd->arg[2]);
			return (1);
		}
		i++;
	}
	return (0);
}

int			set_env(t_cmd *cmd)
{
	int		i;
	char	**tmp;


	i = 0;

	if (check_env(cmd) == 1)
	{
		return (1);
	}
	else
	tmp = cmd->env;
	while (cmd->env[i++])
		tmp[i] = ft_strdup(cmd->env[i]);
	if ((cmd->env = malloc(sizeof(char *) * (i + 1))) == NULL)
		ft_error();
	i = -1;
	while (tmp[++i])
		cmd->env[i] = ft_strdup(tmp[i]);
	cmd->env[i] = ft_strjoin(cmd->arg[1], "=");
	if (cmd->arg[2])
		cmd->env[i] = ft_strjoin(cmd->env[i], cmd->arg[2]);
	return (0);
}

int			ft_unsetenv(t_cmd *cmd)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	while (cmd->env[i])
	{
		k = 0;
		tmp = ft_split_equ(cmd, i);
		while (cmd->arg[++k])
			if (ft_strcmp(tmp, cmd->arg[k]) == 0 && ft_strcmp(tmp, "PWD") != 0)
				cmd->env[i][0] = '\0';
		if (k == 0)
		{
			ft_putendl("unsetenv: Too few arguments.");
			return (k);
		}
		i++;
	}
	return (0);
}
