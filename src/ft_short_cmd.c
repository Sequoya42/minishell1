/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_short_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 15:08:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/13 16:08:03 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_clear_tab(char **tab)
{
	int i;
	int k;

	i = 0;
	if (tab[i] != NULL)
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
