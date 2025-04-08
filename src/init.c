/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:23:48 by hganet            #+#    #+#             */
/*   Updated: 2025/04/08 14:04:29 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Initializes the t_pipex structure: opens files and creates a pipe.
 *
 * Opens argv[1] as infile and initializes the pipe.
 * Outfile is opened later in the second child.
 *
 * @param px Pointer to the t_pipex structure to initialize.
 * @param argv Program arguments.
 * @param envp Environment variables.
 */
void	init_pipex(t_pipex *px, char **argv, char **envp)
{
	// 1 - Initialize the pipex structure and protect against invalid arguments by setting fds to -1
	px->infile = -1; // Initialize infile to -1 to indicate it's not opened
	px->outfile = -1; // Initialize outfile to -1 to indicate it's not opened
	px->pipefd[0] = -1; // Initialize pipe read end to -1 
	px->pipefd[1] = -1; // Initialize pipe write end to -1
	// 2 - Store the command line arguments and environment variables into the structure
	px->argv = argv; // Store the command line arguments to be used in execve
	px->envp = envp; // Store the environment variables to be used in execve
	// 3 - Open the input file and store its file descriptor
	px->infile = open(argv[1], O_RDONLY);
	if (px->infile < 0) // If it fails to open the input file
	{
		perror(argv[1]); // If the file doesn't exist, print the filename like the shell does (argv[1])
		px->infile_opened = 0; // Set infile_opened (flag) to 0 to indicate that the file was not opened
	}
	else
		px->infile_opened = 1; // 4 - Set infile_opened (flag) to 1 to indicate that the file was opened
	if (pipe(px->pipefd) == -1) // 5 - Create a pipe and check for errors (-1)
	{
		perror("Pipe failed"); // If pipe creation fails, print an error message
		if (px->infile_opened) // If the input file was opened, close it
			close(px->infile);
		exit(EXIT_FAILURE); // Exit the program with failure status
	}
}
