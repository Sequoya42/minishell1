/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 15:52:58 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/25 02:51:18 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_update_env(void)
{
	int		i;
	char	*tmp;

	i = 0;
	while (SING->env[i])
	{
		if (ft_strnstr(SING->env[i], "PWD=", 4) != NULL)
		{
			free(SING->env[i]);
			tmp = getcwd(NULL, 0);
			SING->env[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
			tmp = NULL;
		}
		else if (ft_strnstr(SING->env[i], "OLDPWD=", 7) != NULL)
		{
			free(SING->env[i]);
			SING->env[i] = ft_strjoin("OLD", SING->pwd);
		}
 		i++;
	}
}

int		ft_cd_error(void)
{
	int				i;
	struct stat		info;

	i = ft_nb_tab(SING->arg);
	stat(SING->arg[1], &info);
	if (i == 1 && SING->home)
		chdir(SING->home + 5);
	else if (i == 1 && !SING->home)
		ft_putendl("No way home");
	else if (ft_strcmp(SING->arg[1], "-") == 0)
		chdir(SING->oldpwd + 7);
	else if (chdir(SING->arg[1]) == 0)
	{
		ft_update_env();
		return(0);
	}
	else if (S_ISREG(info.st_mode))
		return (ft_error(SING->arg[0], "not a directory", SING->arg[1]));
	else
		return (ft_error(SING->arg[1], NULL, "No such file or directory"));
	ft_update_env();
	return (0);
}

int		ft_change_dir(void)
{
	int i;

	i = ft_nb_tab(SING->arg);
	if (i > 2)
		return(ft_error(SING->arg[0], NULL, "Too many arguments."));
	if (ft_tild(1) == 1)
		return (1);
	else
		ft_cd_error();
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/23 16:38:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/25 02:33:51 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

int		ft_tmp_aff(int l, char **tmp)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (SING->arg[i])
	{
		k = 0;
		while (SING->arg[i][k])
		{
			if (SING->arg[i][k] == '=')
			{
				tmp[l++] = SING->arg[i];
				break ;
			}
			k++;
		}
		i++;
	}
	return (l);
}

int		ft_env_exe(void)
{
	int		i;

	i = 1;
	if (check_current(0) == 1)
		return (1);
	ft_get_pwd();
	while (SING->path[i])
	{
		SING->path[i] = ft_strjoin(SING->path[i], "/");
		SING->path[i] = ft_strjoin(SING->path[i], SING->arg[0]);
		if ((access(SING->path[i], F_OK)) != -1)
		{
			ft_exec(SING->path[i]);
			ft_clear_tab(SING->path);
			SING->path = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

int		ft_env_arg(void)
{
	int		i;
	int		l;
	char	**tmp;

	l = 0;
	ft_get_pwd();
	tmp = malloc(sizeof(*tmp) * ft_nb_tab(SING->arg));
	if (ft_env_exe() == 1)
		return (1);
	if (ft_nb_tab(SING->arg) > 2)
		return (ft_error(SING->arg[0], NULL, "Too many arguments"));
	if (ft_tmp_aff(l, tmp) > 0)
	{
		i = 0;
		while (SING->env[i])
			ft_putendl(SING->env[i++]);
		i = 0;
		while (tmp[i])
			ft_putendl(tmp[i++]);
		return (0);
	}
	else
		ft_error(SING->arg[0], SING->arg[1], "No such file or Directory");
	ft_clear_tab(tmp);
	return (0);
}

int			aff_env(void)
{
	int		i;
	int		k;
	char	**tmp;

	i = 0;
	k = 0;
	if (ft_nb_tab(SING->arg) > 1)
		return (ft_env_arg());
	tmp = ft_update_tab(SING->env);
	while (SING->env[i])
	{
		while (SING->env[i][0] == '\0' && SING->env[i + 1])
			i += 1;
		if (SING->env[i][0] != '\0')
			tmp[k++] = ft_strdup(SING->env[i]);
		i++;
	}
	tmp[k] = NULL;
	ft_clear_tab(SING->env);
	SING->env = NULL;
	SING->env = ft_strdup_tab(tmp);
	ft_clear_tab(tmp);
	tmp = NULL;
	i = 0;
	while (SING->env[i])
		ft_putendl(SING->env[i++]);
	return (0);
}

int			check_env_error(void)
{
	int i;

	i = 0;
	while (SING->arg[1][i])
	{
		if (SING->arg[1][i++] == '=')
		{
			ft_putendl("setenv: Syntax Error");
			return (1);
		}
	}
	i = ft_nb_tab(SING->arg);
	if (i > 3)
	{
		ft_putendl("setenv: too many arguments.");
		return (1);
	}
	return (0);
}

int			check_env(void)
{
	int		i;
	char	*tmp;

	i = 0;
	if (check_env_error() == 1)
		return (1);
	while (SING->env[i])
	{
		tmp = ft_split_char(SING->env[i], 0, '=');
		if (ft_strcmp(tmp, SING->arg[1]) == 0)
		{
			free(SING->env[i]);
			free(tmp);
			tmp = ft_strjoin(SING->arg[1], "=");
			if (SING->arg[2])
				SING->env[i] = ft_strjoin(tmp, \
										  SING->arg[2]);
			else
				SING->env[i] = tmp;
			return (1);
		}
		free(tmp);
		i++;
	}
	return (0);
}

char		*add_env(void)
{
	char	*join;
	char	*join2;

	join = NULL;
	join2 = NULL;
	join = ft_strjoin(SING->arg[1], "=");
	if (SING->arg[2])
	{
		join2 = ft_strjoin(join, SING->arg[2]);
		free(join);
	}
	else
		join2 = join;
	return (join2);
}

int			set_env(void)
{
	int		i;
	char	**tmp;

	if (ft_nb_tab(SING->arg) == 1)
		return (aff_env());
	if (check_env() == 1)
		return (1);
	tmp = ft_strdup_tab(SING->env);
	ft_clear_tab(SING->env);
	SING->env = NULL;
	i = ft_nb_tab(tmp) + 1;
	if ((SING->env = malloc(sizeof(char *) * (i + 1))) == NULL)
		ft_error(NULL, NULL, "Malloc could not allocated memory");
	i = -1;
	while (tmp[++i])
		SING->env[i] = ft_strdup(tmp[i]);
	SING->env[i] = add_env();
	SING->env[i + 1] = NULL;
	ft_clear_tab(tmp);
	tmp = NULL;
	return (0);
}

int			ft_unsetenv(void)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
/* 	if (ft_strcmp(SING->arg[1], "*") == 0) */
/* 	{ */
/* 		ft_clear_tab(SING->env); */
/* 		SING->env[0] = "YOLO"; */
/* 		return (0); */
/* 	} */
	while (SING->env[i])
	{
		k = 0;
		tmp = ft_split_char(SING->env[i], 0, '=');
		while (SING->arg[++k])
		{
			if (ft_strcmp(tmp, SING->arg[k]) == 0)
				SING->env[i][0] = '\0';
			if (ft_strcmp(SING->arg[k], "PATH") == 0)
			{
				ft_putendl("PATH is unset, behavior may be undefined");
				ft_putendl("if you wish to set the variable PATH, type set_path");
				free(tmp);
				return (0);
			}
		}
		free(tmp);
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gest_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:34 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/25 02:36:08 by rbaum            ###   ########.fr       */
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
	SING->name = NULL;
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
	if ((check_current(0) == 1))
		return (1);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 19:45:30 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/25 02:54:15 by rbaum            ###   ########.fr       */
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_short_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 15:08:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/25 02:55:38 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void		ft_exit(void)
{
	int		i;

	i = ft_strlen(SING->name) - 1;
	while (i > 3)
	{
		if (SING->name[i] == ' ' || SING->name[i] == '\t')
			i--;
		else
			break ;
	}
	if (i == 3)
		exit(0);
	if (SING->name[4] != ' ' || SING->name[4] == '\t')
	{
		ft_putstr(SING->name);
		ft_putendl(": Command not found");
	}
	else
		ft_putendl("exit: Expression Syntax");
}

int		ft_if_tild(char *tmp, char *tmp2, int k)
{
	k = 1;
	if (SING->arg[k][0] == '~')
	{
		tmp2 = ft_strjoin(tmp, SING->arg[k] + 1);
		free(SING->arg[k]);
		SING->arg[k] = NULL;
		free(tmp);
		tmp = NULL;
		chdir(tmp2);
		free(tmp2);
		tmp2 = NULL;
		ft_update_env();
		return(1);
	}
	return (0);
}
int		ft_tild(int k)
{
	char	*tmp;
	char	*tmp2;

	tmp = SING->arg[k];
	tmp2 = NULL;
	if (SING->arg[k])
	{
		if (SING->arg[k][0] == '~' || 
			(SING->arg[k][0] == '-' && SING->arg[k][1] == '-'))
		{
			if (SING->home == NULL)
				return(ft_error(SING->arg[0], NULL, "No way home"));
			else
				tmp = ft_strdup(SING->home + 5);
			if (ft_if_tild(tmp, tmp2, k) == 1)
				return (1);
			chdir(tmp);
			free(tmp);
			tmp = NULL;
			free(SING->arg[k]);
			SING->arg[k] = NULL;
			ft_update_env();
			return (1);
		}
	}
	return (0);
}

void		stop_singing(void)
{
	if (SING->path)
	{
		ft_clear_tab(SING->path);
		SING->path = NULL;
	}
	if (SING->pwd)
	{
		SING->pwd = NULL;
		free(SING->pwd);
	}

	if (SING->oldpwd)
	{
		free(SING->oldpwd);
		SING->oldpwd = NULL;
	}
	if (SING->home)
	{
		free(SING->home);
		SING->home = NULL;
	}
}

void		ft_get_pwd(void)
{
	int		i;

	i = 0;

	stop_singing();
    while (SING->env[i])
    {
        if (ft_strnstr(SING->env[i], "PATH=", 5) != NULL)
            SING->path = ft_strsplit(SING->env[i] + 5, ':');
        if (ft_strnstr(SING->env[i], "PWD=", 4) != NULL)
		{
          SING->pwd = ft_strdup(SING->env[i]);
		}
        if (ft_strnstr(SING->env[i], "OLDPWD=", 7) != NULL)
            SING->oldpwd = ft_strdup(SING->env[i]);
        if (ft_strnstr(SING->env[i], "HOME=", 5) != NULL)
			SING->home = ft_strdup(SING->env[i]);
		i++;
    }
/*     printf("adresse 2 %p\n", &(*SING->pwd)); */
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 16:03:48 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/24 20:09:58 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void		sig_return(int signo)
{
	if (signo == SIGINT)
		ft_putendl("");
}

t_cmd		*singleton(void)
{
	static	t_cmd cmd;

	return (&cmd);
}

int			main(int argc, char **argv, char **envp)
{
	argc = argc;
	argv = argv;
	SING->env = malloc(sizeof(char *) * 10);
	if (signal(SIGINT, sig_return) == SIG_ERR)
		ft_prompt();
	if (envp[0])
		SING->env = ft_strdup_tab(envp);
	else
	{
		ft_putendl("Running without env  : Behavior may be undefined");
		ft_putendl("if you wish to set the variable PATH, type set_path");
		SING->env[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		SING->env[1] = ft_strjoin("OLD", SING->env[0] );
	}
	ft_prompt();
	return (0);
}

