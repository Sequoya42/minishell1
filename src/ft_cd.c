/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 15:52:58 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/25 03:20:14 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh1.h"

void	ft_update_env(void)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (SING->env[i])
	{
		if (ft_strnstr(SING->env[i], "PWD=", 4) != NULL)
		{
			tmp2 = ft_strdup(SING->env[i]);
			free(SING->env[i]);
			tmp = getcwd(NULL, 0);
			SING->env[i] = ft_strjoin("PWD=", tmp);
			free(tmp);
			tmp = NULL;
		}
		else if (ft_strnstr(SING->env[i], "OLDPWD=", 7) != NULL)
		{
			free(SING->env[i]);
			SING->env[i] = ft_strjoin("OLD",tmp2);
			free(tmp2);
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
