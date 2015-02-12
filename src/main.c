/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 16:03:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/11 21:42:03 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int         main(int argc, char **argv, char **envp)
{
    t_cmd   *cmd;

    argc = argc;
    argv = argv;
	cmd = malloc(sizeof(t_cmd));
	cmd->env = envp;
    ft_prompt(cmd);
    return (0);
}
