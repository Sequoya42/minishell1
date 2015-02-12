/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sh1.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/11 15:34:58 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/12 21:14:59 by marvin           ###   ########.fr       */
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
	char	**env;
	char	**arg;
};

void		ft_prompt(t_cmd *cmd);
void		ft_gest_cmd(t_cmd *cmd);
void		ft_get_right_cmd(t_cmd *cmd);
void		aff_env(t_cmd *cmd);
void		ft_error(void);

int			check_env(t_cmd *cmd);
int			set_env(t_cmd *cmd);
int			ft_unsetenv(t_cmd *cmd);

#endif