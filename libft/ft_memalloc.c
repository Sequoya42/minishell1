/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 18:42:24 by rbaum             #+#    #+#             */
/*   Updated: 2014/11/08 17:03:28 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*mem;
	char	*t;

	i = 0;
	mem = (void *)malloc(size * sizeof(void));
	t = (char *)mem;
	if (mem != NULL)
	{
		while (i < size)
		{
			*t++ = 0;
			i++;
		}
	}
	return (mem);
}
