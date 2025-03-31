/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:23:48 by hganet            #+#    #+#             */
/*   Updated: 2025/03/31 18:17:44 by hganet           ###   ########.fr       */
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
void	init_pipex(t_pipex *px, char **argv, char **envp)
{
	px->argv = argv;
	px->envp = envp;
	px->infile = open(argv[1], O_RDONLY);
	if (px->infile < 0)
	{
		perror(argv[1]);	   // Print file error like the shell
		px->infile_opened = 0; // Flag to handle fallback
	}
	else
		px->infile_opened = 1;
	px->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (px->outfile < 0)
	{
		perror("Error opening outfile");
		close(px->infile);
		exit(EXIT_FAILURE);
	}
	if (pipe(px->pipefd) == -1)
	{
		perror("Pipe failed");
		exit(EXIT_FAILURE);
	}
}
