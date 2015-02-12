/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:30 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/13 00:09:14 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_prompt(t_cmd *cmd)
{
	int		ret;
	char	*line;

	ft_putstr("no_prompt>$ ");
	while ((ret = get_next_line(1, &line)) != 0)
    {
        cmd->name = ft_strdup(line);
        ft_gest_cmd(cmd);
		ft_putchar('\n');
		ft_putstr("no_prompt>$ ");

	}
}
