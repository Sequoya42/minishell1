/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:30 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/13 22:53:33 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_prompt(t_cmd *cmd)
{
	int		ret;
	int		stat;
	char	*line;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid > 0)
		waitpid(pid, &stat, 0);
	else
		ft_putendl("mon pid = 0 j'ai lancer le fils!");// execve(awdawd)

	ft_putstr("no_prompt>$ ");
	while ((ret = get_next_line(1, &line)) != 0)
    {
        cmd->name = ft_strdup(line);
        ft_gest_cmd(cmd);
		ft_putchar('\n');
		ft_putstr("no_prompt>$ ");
	}
}

/*
Fork->execve->acces->check_path(to see if "ls" is part of /bin/"ls" for example)
Fork only when needed
Then CD
