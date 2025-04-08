/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:42:49 by hganet            #+#    #+#             */
/*   Updated: 2025/04/08 14:09:58 by hganet           ###   ########.fr       */
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
 * @brief Structure to store pipex program state and shared variables.
 */
typedef struct s_pipex
{
	int		pipefd[2]; // Pipe file descriptors: [0] for read end, [1] for write end
	int		infile; // File descriptor for the input file
	int		outfile; // File descriptor for the output file
	int		infile_opened; // Flag to indicate if the input file was successfully opened
	pid_t	pid1; // Process ID for the first child process
	pid_t	pid2; // Process ID for the second child process
	char	**argv; // Command line arguments: argv[1] = infile, argv[2] = cmd1, argv[3] = cmd2, argv[4] = outfile
	char	**envp; // Environment variables passed to execve
}			t_pipex;

void	init_pipex(t_pipex *px, char **argv, char **envp);
void	exec_first_child(t_pipex *px);
void	exec_second_child(t_pipex *px);
void	close_fds(t_pipex *px);
void	free_split(char **arr);
char	**parse_cmd(char *cmd_str, char **envp, char **cmd_path_out);
char	*get_cmd_path(char *cmd, char **envp);

#endif