/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:46:23 by hganet            #+#    #+#             */
/*   Updated: 2025/04/08 13:23:53 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Sets up STDIN for the first child.
 *
 * If infile was successfully opened, redirects it to STDIN.
 * Otherwise, redirects /dev/null to STDIN to simulate an empty file.
 *
 * @param px Pointer to the pipex structure.
 */
static void	handle_infile(t_pipex *px)
{
	int	devnull;

	if (!px->infile_opened)
	{
		devnull = open("/dev/null", O_RDONLY);
		if (devnull < 0)
		{
			perror("open /dev/null");
			exit(1);
		}
		dup2(devnull, STDIN_FILENO);
		close(devnull);
	}
	else
		dup2(px->infile, STDIN_FILENO);
}

/**
 * @brief Opens and redirects the output file for the second child.
 *
 * Opens the output file in truncate/write mode and redirects it to STDOUT.
 * Exits with error if the file can't be opened.
 *
 * @param px Pointer to the pipex structure.
 */
static void	handle_outfile(t_pipex *px)
{
	px->outfile = open(px->argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (px->outfile < 0)
	{
		perror(px->argv[4]);
		exit(EXIT_FAILURE);
	}
	dup2(px->outfile, STDOUT_FILENO);
}

/**
 * @brief Parses and executes the given command using execve.
 *
 * Resolves the binary path using PATH from envp.
 * If resolution fails, frees memory and exits with code 127.
 * If execve fails, reports and exits.
 *
 * @param cmd_str The raw command string (e.g., "ls -l").
 * @param envp The environment passed from main.
 */
static void	execute_command(char *cmd_str, char **envp)
{
	char	*cmd_path;
	char	**args;

	args = parse_cmd(cmd_str, envp, &cmd_path);
	if (!args)
	{
		perror("Command not found");
		exit(127);
	}
	execve(cmd_path, args, envp);
	perror("execve failed");
	free(cmd_path);
	free_split(args);
	exit(1);
}

/**
 * @brief Forks and runs the first child process (cmd1).
 *
 * Redirects infile or /dev/null to STDIN, pipe write end to STDOUT,
 * then runs the first command.
 *
 * @param px Pointer to the initialized pipex structure.
 */
void	exec_first_child(t_pipex *px)
{
	px->pid1 = fork();
	if (px->pid1 == -1)
		perror("Fork failed");
	if (px->pid1 == 0)
	{
		handle_infile(px);
		dup2(px->pipefd[1], STDOUT_FILENO);
		close_fds(px);
		execute_command(px->argv[2], px->envp);
	}
}

/**
 * @brief Forks and runs the second child process (cmd2).
 *
 * Redirects pipe read end to STDIN, outfile to STDOUT,
 * then runs the second command.
 *
 * @param px Pointer to the initialized pipex structure.
 */
void	exec_second_child(t_pipex *px)
{
	px->pid2 = fork();
	if (px->pid2 == -1)
		perror("Fork failed");
	if (px->pid2 == 0)
	{
		dup2(px->pipefd[0], STDIN_FILENO);
		handle_outfile(px);
		close_fds(px);
		execute_command(px->argv[3], px->envp);
	}
}
