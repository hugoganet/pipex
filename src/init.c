/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:23:48 by hganet            #+#    #+#             */
/*   Updated: 2025/03/31 18:33:34 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Initializes the t_pipex structure: opens files and creates a pipe.
 *
 * Opens argv[1] as infile and argv[4] as outfile.
 * If anything fails, prints error and exits the program.
 *
 * @param px Pointer to the t_pipex structure to initialize.
 * @param argv Program arguments.
 * @param envp Environment variables.
 */
void init_pipex(t_pipex *px, char **argv, char **envp)
{
	// 1. Initialize all fds to -1 (so close_fds() won't crash if called early)
	px->infile = -1;
	px->outfile = -1;
	px->pipefd[0] = -1;
	px->pipefd[1] = -1;

	// 2. Save args and env
	px->argv = argv;
	px->envp = envp;

	// 3. Try to open infile
	px->infile = open(argv[1], O_RDONLY);
	if (px->infile < 0)
	{
		perror(argv[1]);	   // Shell prints the filename
		px->infile_opened = 0; // Mark as not opened
	}
	else
		px->infile_opened = 1;

	// 4. Create the pipe
	if (pipe(px->pipefd) == -1)
	{
		perror("Pipe failed");
		if (px->infile_opened)
			close(px->infile); // Close infile if it was opened
		exit(EXIT_FAILURE);
	}

	// ✅ outfile will be opened later in exec_second_child()
}
