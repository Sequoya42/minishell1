/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_short_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 15:08:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/15 22:36:34 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

char		*ft_split_equ(t_cmd *cmd, int i)
{
	int		k;
	char	*tmp;

	k = 0;
	while (cmd->env[i][k] != '=')
		k++;
	tmp = ft_strnew(k);
	ft_strncpy(tmp, cmd->env[i], k);
	return (tmp);
}

void		ft_exit(t_cmd *cmd)
{
	int		i;

	i = ft_strlen(cmd->name) - 1;
	while (i > 3)
	{
		if (cmd->name[i] == ' ' || cmd->name[i] == '\t')
			i--;
		else
			break ;
	}
	if (i == 3)
		exit(0);
	if (cmd->name[4] != ' ' || cmd->name[4] == '\t')
	{
		ft_putstr(cmd->name);
		ft_putendl(": Command not found");
	}
	else
		ft_putendl("exit: Expression Syntax");
}

void		ft_tild(t_cmd *cmd, int k)
{
	char	*tmp;

	if (cmd->arg[k])
	{
		if (cmd->arg[k][0] == '~')
		{
			tmp = ft_strdup(cmd->arg[k]);
			cmd->arg[k] = ft_strdup(cmd->home + 5);
			cmd->arg[k] = ft_strjoin(cmd->arg[1], tmp + 1);
		}
	}
}

void		ft_get_pwd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->env[i])
	{
		if (ft_strnstr(cmd->env[i], "PATH=", 5) != NULL)
			cmd->path = ft_strsplit(cmd->env[i] + 5, ':');
		if (ft_strnstr(cmd->env[i], "PWD=", 4) != NULL)
			cmd->pwd = ft_strdup(cmd->env[i]);
		if (ft_strnstr(cmd->env[i], "OLDPWD=", 7) != NULL)
			cmd->oldpwd = ft_strdup(cmd->env[i]);
		if (ft_strnstr(cmd->env[i], "HOME=", 5) != NULL)
			cmd->home = ft_strdup(cmd->env[i]);
		i++;
	}
}
