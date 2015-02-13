/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 19:39:12 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/13 16:09:26 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"


int    aff_env(t_cmd *cmd)
{
    int i;
	int k;
	char **tmp;

   i = 0;
   k = 0;
   while (cmd->env[i])
   {
	   if (cmd->env[i][0] == '\0')
		   k++;
	   i++;
   }
   if ((tmp = malloc(sizeof(char*) * (i - k) + 1)) == NULL)
	   return (ft_error());
   i = 0;
   k = 0;
   while (cmd->env[i])
   {
        while (cmd->env[i][0] == '\0' && cmd->env[i + 1])
			i += 1;
		if (cmd->env[i])
			ft_putendl(tmp[k++] = cmd->env[i++]);
   }
   cmd->env = tmp;
   return (0);
}

int     check_env(t_cmd *cmd)
{
    int i;
	char *tmp;

    i = 0;
	while (cmd->arg[i])
		i++;
	if (i == 0)
		return (aff_env(cmd));
	else if (i != 2 && i != 0)
		return (ft_error());
	i = 0;
    while (cmd->env[i])
    {
		tmp = ft_split_equ(cmd, i);
		if (ft_strcmp(tmp, cmd->arg[0]) == 0)
		{
			cmd->env[i] = ft_strjoin(cmd->arg[0], "=");
			cmd->env[i] = ft_strjoin(cmd->env[i], cmd->arg[1]);
			return (1);
		}
        i++;
    }
    return (0);
}

int     set_env(t_cmd *cmd)
{
    int		i;
	char	**tmp;

    i = 0;
    cmd->name = cmd->name + 7;
	cmd->arg = ft_strsplit(cmd->name, ' ');
    if (check_env(cmd) == 1)
        return (1);
        tmp = cmd->env;
        while (cmd->env[i++])
            tmp[i] = ft_strdup(cmd->env[i]);
        if ((cmd->env = malloc(sizeof(char *) * (i + 1))) == NULL)
            ft_error();
        i = -1;
        while (tmp[++i])
            cmd->env[i] = ft_strdup(tmp[i]);
		cmd->env[i] = ft_strjoin(cmd->arg[0], "=");
		cmd->env[i] = ft_strjoin(cmd->env[i], cmd->arg[1]);
    return (0);
}

int     ft_unsetenv(t_cmd *cmd)
{
    int i;
	int k;
	char *tmp;

    i = 0;
    cmd->name = cmd->name + 9;
	if (cmd->arg)
		ft_clear_tab(cmd->arg);
	cmd->arg = ft_strsplit(cmd->name, ' ');
    while (cmd->env[i])
    {
		k = -1;
		tmp = ft_split_equ(cmd, i);
		while (cmd->arg[++k])
			if (ft_strcmp(tmp, cmd->arg[k]) == 0)
				cmd->env[i][0] = '\0';
		i++;
    }
    return (0);
}
