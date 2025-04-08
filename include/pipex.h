/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:42:49 by hganet            #+#    #+#             */
/*   Updated: 2025/04/08 13:24:34 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stddef.h>
# include "libft.h"

/**
 * @struct t_pipex
 * @brief Struct to store pipex program state and shared variables.
 */
typedef struct s_pipex
{
	int		pipefd[2];
	int		infile;
	int		outfile;
	int		infile_opened;
	pid_t	pid1;
	pid_t	pid2;
	char	**argv;
	char	**envp;
}			t_pipex;

void	init_pipex(t_pipex *px, char **argv, char **envp);
void	exec_first_child(t_pipex *px);
void	exec_second_child(t_pipex *px);
void	close_fds(t_pipex *px);
void	free_split(char **arr);
char	**parse_cmd(char *cmd_str, char **envp, char **cmd_path_out);
char	*get_cmd_path(char *cmd, char **envp);

#endif