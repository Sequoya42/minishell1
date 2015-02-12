/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 19:39:12 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/12 23:09:45 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void    aff_env(t_cmd *cmd)
{
    int i;

    i = 0;
    while (cmd->env[i])
    {
        while (cmd->env[i][0] == '\0')
            i += 1;
        if (cmd->env[i])
            ft_putendl(cmd->env[i++]);
    }
}

int     check_env(t_cmd *cmd)
{
    int i;

    i = 0;
	cmd->arg = ft_strsplit(cmd->name, ' ');
	i = 0;
	while (cmd->arg[i])
		i++;
	if (i > 2)
		ft_error();
	if (i == 0)
		aff_env(cmd);
	i = 0;
    while (cmd->env[i])
    {
        int k = 0;
        while (cmd->env[i][k] == cmd->name[k])
        {
            if (cmd->name[k + 1] == ' ')
            {
				cmd->env[i] = ft_strjoin(cmd->arg[0], "=");
				cmd->env[i] = ft_strjoin(cmd->env[i], cmd->arg[1]);
                return (1);
            }
            k++;
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

int     ft_unsetenv2(t_cmd *cmd)
{
    int i;
    int j;

    i = 0;
    cmd->name = cmd->name + 9;
    while (cmd->env[i])
    {
        j = 0;
        while (cmd->env[i][j] != '=')
            j++;
        if (ft_strnstr(cmd->env[i], cmd->name, j))
        {
            cmd->env[i][0] = '\0';
            return (1);
        }
        i++;
    }
    return (0);
}

int		ft_unsetenv(t_cmd *cmd)
{
	int i = 0;
	while (cmd->env[i++])
		ft_unsetenv2(cmd);
	return (0);
}
