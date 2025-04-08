/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:46:23 by hganet            #+#    #+#             */
/*   Updated: 2025/04/08 14:49:56 by hganet           ###   ########.fr       */
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
	int	devnull; // File descriptor for /dev/null

	if (!px->infile_opened) // If infile was not opened successfully
	{
		// Open /dev/null to simulate empty input when the infile doesn't exist.
		// It's like handing an empty file to the command.
		devnull = open("/dev/null", O_RDONLY);
		{
			perror("open /dev/null"); // Print error message for /dev/null
			exit(1); // Exit with failure status
		}
		dup2(devnull, STDIN_FILENO); // Redirect STDIN to /dev/null
		close(devnull); // Close the /dev/null file descriptor
	}
	else // If infile was opened successfully
		dup2(px->infile, STDIN_FILENO);  // Redirect STDIN to the opened infile
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

	// 1 - Get the command path using the provided command string and environment variables
	args = parse_cmd(cmd_str, envp, &cmd_path);
	if (!args) // If parsing the command fails
	{
		perror("Command not found"); // Print error message for command not found
		exit(127);					 // Exit with code 127, a standard UNIX shell code for "command not found"
	}
	// 2 - Replace current process with the given command using execve.
	// If it succeeds, it never returns. If it fails, the code below runs.
	execve(cmd_path, args, envp);
	// The check "if execve fails" is done implicitly: because if it succeeds, you never return.
	// If execve fails, it returns -1 and we land here to report the error.
	perror("execve failed"); // Print error message if execve fails
	free(cmd_path); // Free the command path memory
	free_split(args); // Free the arguments array
	exit(1); // Exit with failure status
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
	// 1 - Fork a new process for the first command
	px->pid1 = fork(); 
	if (px->pid1 == -1) // Check for fork error
		perror("Fork failed"); // Print error message if fork fails
	if (px->pid1 == 0) // If in the child process
	{
		// 2 - If infile was opened successfully, redirect it to STDIN,
		// 	   otherwise redirect STDIN to /dev/null to simulate an empty file and avoid errors
		handle_infile(px);
		// 3 - Redirect stdout to the pipe's write end, so cmd1 sends output into the pipe.
		dup2(px->pipefd[1], STDOUT_FILENO);
		// 4 - // Close all file descriptors: avoids leaks and prevents blocking behavior in pipes.
		close_fds(px);
		// 5 - Execute the first command
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
	// 1 - Fork a new process for the second command
	px->pid2 = fork();
	if (px->pid2 == -1) // Check for fork error
		perror("Fork failed"); // Print error message if fork fails
	if (px->pid2 == 0)
	{
		// 2 - Replace the terminal (STDIN) with the pipe’s read end.
		dup2(px->pipefd[0], STDIN_FILENO);
		// 3 - Close the pipe write end and the infile file descriptor
		handle_outfile(px);
		// 4 - Close all file descriptors to avoid leaks
		close_fds(px);
		// 5 - Execute the second command
		execute_command(px->argv[3], px->envp);
	}
}
