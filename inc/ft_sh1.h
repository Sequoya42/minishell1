/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 15:34:58 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/18 19:18:16 by rbaum            ###   ########.fr       */
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

struct		s_cmd
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
void		ft_exec(t_cmd *cmd, char *path);
void		ft_get_pwd(t_cmd *cmd);
void		ft_exit(t_cmd *cmd);
void		ft_tild(t_cmd *cmd, int k);
void		ft_update_env(t_cmd *cmd);
void		ft_go_home(t_cmd *cmd);
void		ft_previous_dir(t_cmd *cmd);
void		ft_cd_error(t_cmd *cmd);

int			ft_change_dir(t_cmd *cmd);
int			ft_error(void);
int			check_current(t_cmd *cmd, int k);
int			check_path(t_cmd *cmd);
int			check_env(t_cmd *cmd);
int			aff_env(t_cmd *cmd);
int			set_env(t_cmd *cmd);
int			ft_unsetenv(t_cmd *cmd);
int			ft_nb_tab(char **tab);

char		*ft_split_equ(t_cmd *cmd, int i);
char		**pre_aff(t_cmd *cmd);

#endif
