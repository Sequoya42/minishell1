/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/15 19:50:14 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/24 22:34:43 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_clear_tab(char **tab)
{
	int		i;

	i = 0;
	if (tab == NULL)
		tab = NULL;
	else
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
		tab = NULL;
	}
}
