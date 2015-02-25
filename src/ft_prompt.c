/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:30 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/25 02:56:58 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
		ft_prompt();
	}
}

void	ft_exec(char *path)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid == -1)
		ft_error("", "", "Pid error");
	if (pid > 0)
	{
		waitpid(pid, &stat, 0);
		if (signal(SIGINT, sig_handler) == SIG_ERR)
			ft_prompt();
	}
	else
		execve(path, SING->arg, SING->env);
}

void			ft_name_prompt(void)
{
	char *tmp;
	char *tmp2;

	tmp2 = getcwd(NULL, 0);
	tmp = ft_strrchr(tmp2, '/');
	ft_putchar('[');
	ft_putstr(tmp + 1);
	ft_putstr("] prompt>$ ");
 	free(tmp2);

}

void			ft_prompt(void)
{
	int			ret;
	char		*line;

	ft_name_prompt();
	SING->path = malloc(sizeof(char*) * 10);
	while ((ret = get_next_line(1, &line)) != 0)
	{
		SING->name = ft_strdup(line);
		ft_get_right_cmd();
		SING->arg = ft_strsplit(SING->name, ' ');
		ft_get_pwd();
		ft_gest_cmd();

		free(line);
		line = NULL;
		stop_singing();
		free(SING->name);
		SING->name = NULL;
		if (SING->arg != NULL)
		{
			ft_clear_tab(SING->arg);
			SING->arg = NULL;
		}
		ft_name_prompt();
	}
}
