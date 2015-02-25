/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_short_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 15:08:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/25 03:43:30 by rbaum            ###   ########.fr       */
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
			SING->pwd = SING->env[i];
        if (ft_strnstr(SING->env[i], "OLDPWD=", 7) != NULL)
            SING->oldpwd = SING->env[i];
        if (ft_strnstr(SING->env[i], "HOME=", 5) != NULL)
			SING->home = SING->env[i];
		i++;
    }
}
