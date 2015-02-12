/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/12 19:39:12 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/13 00:53:49 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void    aff_env(t_cmd *cmd)
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
	   ft_error();
   i = 0;
   k = 0;
   while (cmd->env[i])
   {
        while (cmd->env[i][0] == '\0' && cmd->env[i + 1])
			i += 1;
		if (cmd->env[i])
		{
			tmp[k++] = cmd->env[i++];
			ft_putendl(tmp[k - 1]);
		}
   }
   cmd->env = tmp;
}

int     check_env(t_cmd *cmd)
{
    int i;
	char *tmp;

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
		tmp = ft_strchr(cmd->env[i], '=');
        while (tmp[k] == cmd->name[k])
        {
            if (cmd->name[k + 1] == ' ' && tmp[k + 1] == '=')
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
    int j;
	int k;

    i = 0;
    cmd->name = cmd->name + 9;
	cmd->arg = NULL;
	cmd->arg = ft_strsplit(cmd->name, ' ');
    while (cmd->env[i])
    {
        j = 0;
		k = 0;
        while (cmd->env[i][j] != '=')
            j++;
		ft_putnbrn(j);
		while (cmd->arg[k])
		{
			if (ft_strnstr(cmd->env[i], cmd->arg[k], j) && \
				cmd->env[i][0] == cmd->arg[k][0])
			{
				if (cmd->env[i][j] == '=')
				{
					ft_putnbrn(j);
				cmd->env[i][0] = '\0';
				}
				break;
			}
			k++;
		}
        i++;
    }
    return (0);
}
