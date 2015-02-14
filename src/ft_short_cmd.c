/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_short_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 15:08:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/14 18:13:56 by rbaum            ###   ########.fr       */
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
