/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 16:03:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/18 18:40:48 by rbaum            ###   ########.fr       */
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
	if (!envp[0])
	{
		cmd->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		cmd->env[1] = ft_strjoin("OLD=", cmd->env[0]);
		ft_putendl("Running without env  : Behavior may be undefined");
		ft_putendl("if you wish to set the variable PATH, type set_path");
	}
	ft_prompt(cmd);
	return (0);
}

// Rediriger les erreurs sur la sortie d'erreur
