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
