/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:34 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/13 00:12:10 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_error(void)
{
	ft_putendl("Unknown Error");
}

void	ft_get_right_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	while ((*cmd->name == ' ' || *cmd->name == '\t'))
		cmd->name++;
	while (cmd->name[i])
	{
		while (cmd->name[i] == '\t')
			cmd->name[i] = ' ';
		i++;
	}
}

void	ft_gest_cmd(t_cmd *cmd)
{
	ft_get_right_cmd(cmd);
	if (ft_strnstr(cmd->name, "exit", 4) != NULL)
		exit(0);
	else if(ft_strnstr(cmd->name, "setenv", 6) != NULL)
		set_env(cmd);
	else if(ft_strnstr(cmd->name, "env", 3) != NULL)
		aff_env(cmd);
	else if (ft_strnstr(cmd->name, "unsetenv", 8) != NULL)
		ft_unsetenv(cmd);
	else
		ft_error();
}
