/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:53:50 by hganet            #+#    #+#             */
/*   Updated: 2025/03/31 15:07:25 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
int main(int argc, char **argv, char **envp)
{
	t_pipex px;

	if (argc != 5)
		return (write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38), 1);
	init_pipex(&px, argv, envp);
	printf("input.txt = %i\noutput.txt = %i\n", px.infile, px.outfile);
	exec_first_child(&px);
	exec_second_child(&px);
	close_fds(&px);
	return (0);
}
