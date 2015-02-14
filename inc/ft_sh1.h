/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 15:34:58 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/14 18:25:16 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SH1_H
# define FT_SH1_H

# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include "libft.h"

typedef struct s_cmd		t_cmd;

struct s_cmd
{
	char	*name;
	char	*home;
	char	*pwd;
	char	*oldpwd;
	char	**path;
	char	**env;
	char	**arg;
};

void		ft_prompt(t_cmd *cmd);
void		ft_gest_cmd(t_cmd *cmd);
void		ft_get_right_cmd(t_cmd *cmd);
void		ft_clear_tab(char **tab);
void		ft_exec(t_cmd *cmd, int i);
void		ft_get_pwd(t_cmd *cmd);
void		ft_exit(t_cmd *cmd);

int			ft_error(void);
int			check_env(t_cmd *cmd);
int			aff_env(t_cmd *cmd);
int			set_env(t_cmd *cmd);
int			ft_unsetenv(t_cmd *cmd);
int			ft_nb_tab(char **tab);

char		*ft_split_equ(t_cmd *cmd, int i);

#endif
