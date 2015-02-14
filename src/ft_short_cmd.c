/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_short_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 15:08:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/14 23:55:08 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_clear_tab(char **tab)
{
	int i;
	int k;

	i = 0;
	if (tab == NULL)
		tab = NULL;
	else
	{
		while (tab[i])
		{
			k = ft_strlen(tab[i]);
			while (tab[i][k])
			{
				tab[i][k] = '\0';
				k--;
			}
			i++;
		}
		tab = NULL;
	}
}

char	*ft_split_equ(t_cmd *cmd, int i)
{
	int k;
	char *tmp;

	k = 0;
	while (cmd->env[i][k] != '=')
		k++;
	tmp = ft_strnew(k);
	ft_strncpy(tmp, cmd->env[i], k);
	return (tmp);
}

void	ft_exit(t_cmd *cmd)
{
	int i;

	i = ft_strlen(cmd->name) - 1;
	while (i > 3)
	{
		if (cmd->name[i] == ' ' || cmd->name[i] == '\t')
			i--;
		else
			break;
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

int		ft_nb_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_get_back(char *str, t_cmd *cmd)
{
	int i;
	char *tmp;
	int k = 0;
	k = k;
	cmd = cmd;
	while (cmd->arg[k])
		ft_putendl(cmd->arg[k++]);
	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	tmp = ft_strndup(str, i);
	return (tmp);
}

void	ft_tild(t_cmd *cmd, int k)
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
