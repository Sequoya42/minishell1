/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 16:03:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/15 20:02:05 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int			main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;

	argc = argc;
	argv = argv;
	cmd = malloc(sizeof(t_cmd));
	cmd->env = envp;
	if (ft_nb_tab(cmd->env) < 2)
	{
		ft_putendl("Cannot run without env");
		exit(-1);
	}
	ft_prompt(cmd);
	return (0);
}
