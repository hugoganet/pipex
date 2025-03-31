/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:46:23 by hganet            #+#    #+#             */
/*   Updated: 2025/03/31 15:47:07 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Executes the first child process (cmd1).
 * Redirects infile to stdin, and pipe write end to stdout.
 *
 * @param px Pointer to the initialized pipex structure.
 */
void exec_first_child(t_pipex *px)
{
	char *cmd_path;
	char **args;

	px->pid1 = fork();
	if (px->pid1 == -1)
		perror("Fork failed");
	if (px->pid1 == 0)
	{
		dup2(px->infile, STDIN_FILENO); // The process now listen from input.txt
		dup2(px->pipefd[1], STDOUT_FILENO); // The process now write into pipe's WRITE end (pipefd[1])
		close_fds(px);
		args = parse_cmd(px->argv[2], px->envp, &cmd_path);
		if (!cmd_path)
		{
			perror("Command not found");
			exit(127);
		}
		execve(cmd_path, args, px->envp);
		perror("execve failed");
		free(cmd_path);
		free_split(args);
		exit(1);
	}
}

/**
 * @brief Executes the second child process (cmd2).
 * Redirects pipe read end to stdin, and outfile to stdout.
 *
 * @param px Pointer to the initialized pipex structure.
 */
void exec_second_child(t_pipex *px)
{
	char *cmd_path;
	char **args;

	px->pid2 = fork();
	if (px->pid2 == -1)
		perror("Fork failed");
	if (px->pid2 == 0)
	{
		dup2(px->pipefd[0], STDIN_FILENO);
		dup2(px->outfile, STDOUT_FILENO);
		close_fds(px);
		args = parse_cmd(px->argv[3], px->envp, &cmd_path);
		if (!cmd_path)
		{
			perror("Command not found");
			exit(127);
		}
		execve(cmd_path, args, px->envp);
		perror("execve failed");
		free(cmd_path);
		free_split(args);
		exit(1);
	}
}
