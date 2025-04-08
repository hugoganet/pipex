/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:53:50 by hganet            #+#    #+#             */
/*   Updated: 2025/04/08 14:00:19 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


/**
 * @brief Entry point of the pipex program. Orchestrates the execution
 * of two commands connected via a pipe, simulating shell piping.
 *
 * @param argc Argument count (must be 5).
 * @param argv Argument vector: file1, cmd1, cmd2, file2.
 * @param envp Environment variables passed to execve.
 * @return int Exit status code.
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;
	int		status;

	if (argc != 5)
		return (write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38), 1);
	// 1- Initialize the pipex structure, open files, and create a pipe.
	init_pipex(&px, argv, envp);
	// 2- Forks and launches first command (cmd1)
	exec_first_child(&px);
	// 3- Forks and launches second command (cmd2)
	exec_second_child(&px);
	// 4- Close the pipe file descriptors
	close_fds(&px);
	// 5- Wait for first child process to finish (pid1)
	waitpid(px.pid1, NULL, 0);
	// 6- Wait for second child process to finish (pid2)
	waitpid(px.pid2, &status, 0);
	// 7- Check the exit status of the second child process (pid2)
)	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); // Return the exit status of the second child process if it exited normally.
	else
		return (1); // Return 1 if the second child process did not exit normally.
}
