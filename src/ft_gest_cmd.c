/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:34 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/25 03:00:35 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_get_right_cmd(void)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(SING->name);
	while ((tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	j = i;
	while (tmp[i])
	{
		if (tmp[i] == '\t')
			tmp[i] = ' ';
		i++;
	}
	free(SING->name);
	SING->name = ft_strdup(tmp + j);
	free(tmp);
}

int		check_current(int k)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	ft_tild(0);
	while (SING->env[i])
	{
		if (ft_strnstr(SING->env[i], "PWD=", 4) != NULL)
			tmp = ft_strdup(SING->env[i] + 4);
		i++;
 	}
	tmp2 = ft_strjoin(tmp, "/");
	tmp = ft_strjoin(tmp2, SING->arg[k]);
	free(tmp2);
	if ((access(tmp, F_OK)) != -1)
	{
		ft_exec(tmp);
		free(tmp);
		return (1);
	}
	if ((access(SING->arg[k], F_OK)) != -1)
	{
		ft_exec(SING->arg[k]);
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int		check_path(char **arg)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;

	ft_get_pwd();
//	if ((check_current(0) == 1))
//		return (1);
	if (SING->path == NULL)
		return (ft_error(NULL, arg[0], "Command not found."));
	while (SING->path[i])
	{
		tmp = ft_strjoin(SING->path[i], "/");
		free(SING->path[i]);
		tmp2 = ft_strjoin(tmp, arg[0]);
		SING->path[i] = ft_strdup(tmp2);
		free(tmp);
		free(tmp2);
		if ((access(SING->path[i], F_OK)) != -1)
		{
			ft_exec(SING->path[i]);
			return (1);
		}
		i++;
	}
	return (ft_error(NULL, arg[0], "Command not found."));
}

void	ft_create_env(void)
{
	ft_putendl("Var PATH is set");
	SING->env[0] = ft_strdup("PATH=/usr/local/bin:/usr/bin:\
/bin:/usr/sbin:/sbin:/opt/X11/bin:/usr/texbin:\
/nfs/zfs-student-5/users/2014_paris/rbaum/.brew/bin");
	SING->env[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	SING->env[2] = ft_strjoin("OLD=", SING->env[1]);
}

void	ft_gest_cmd(void)
{

	if (ft_strcmp(SING->arg[0], "exit") == 0)
		ft_exit();
	else if (ft_strcmp(SING->arg[0], "setenv") == 0)
		set_env();
	else if (ft_strcmp(SING->arg[0], "env") == 0)
		aff_env();
	else if (ft_strcmp(SING->arg[0], "unsetenv") == 0)
		ft_unsetenv();
	else if (ft_strcmp(SING->arg[0], "cd") == 0)
		ft_change_dir();
	else if (SING->arg[0] == '\0')
		SING->name = SING->name;
	else if (ft_strcmp(SING->arg[0], "set_path") == 0)
		ft_create_env();
	else
		check_path(SING->arg);
	stop_singing();
}
