/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 16:03:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/11 19:03:35 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int         main(int argc, char **argv)
{
    char    *line;
    int     ret;
    t_cmd   *cmd;
    int     i;

    i = 0;
    argc = argc;
    argv = argv;
    cmd = malloc(sizeof(t_cmd));
    ft_prompt(cmd);
    while ((ret = ft_gnl(1, &line)) != 0)
    {
        cmd->name = ft_strdup(line);
        ft_gest_cmd(cmd);
        ft_prompt(cmd);
    }
    return (0);
}
