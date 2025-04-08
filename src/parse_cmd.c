/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:16:13 by hganet            #+#    #+#             */
/*   Updated: 2025/04/08 15:04:24 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Finds the full path to a command using the PATH env variable.
 *
 * @param cmd Command name (e.g. "ls").
 * @param envp Environment variables array.
 * @return char* Path to the executable, or NULL if not found.
 */
char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	char	*joined;
	int		i;

	i = 0;
	// 1 - Look for the environment variable that starts with "PATH="
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL); // PATH not found (rare but possible in minimal envs)
	// 🧪 Remove the "PATH=" part and split the remaining string by ':'
	// Example: "/usr/bin:/bin:/usr/local/bin"
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		// 🔧 Build the full path candidate: "/usr/bin/" + "ls" → "/usr/bin/ls"
		joined = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(joined, cmd);
		free(joined);
		// ✅ Check if this file exists and is executable
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);	// Clean up the array before returning
			return (full_path); // Return the first valid executable we find
		}
		// ❌ Didn't work, try next directory
		free(full_path);
		i++;
	}
	// 🧹 If we reach this point, nothing was found → clean up
	free_split(paths);
	return (NULL);
}

/**
 * @brief Splits a command string into args and resolves its binary path.
 *
 * @param cmd_str Raw command string (e.g. "ls -l").
 * @param envp Environment variables.
 * @param cmd_path_out Output pointer for the resolved command path.
 * @return char** Parsed arguments for execve (NULL-terminated).
 */
char	**parse_cmd(char *cmd_str, char **envp, char **cmd_path_out)
{
	char	**args;

	// 🔩 Break the string into parts using space: "ls -l" → {"ls", "-l", NULL}
	args = ft_split(cmd_str, ' ');
	if (!args || !args[0]) // if empty string or failed allocation
	{
		free_split(args); // make sure to avoid leaks
		return (NULL);
	}
	// 🔎 Use get_cmd_path to find where the binary (e.g. "ls") is located
	*cmd_path_out = get_cmd_path(args[0], envp);
	// ❌ If the command couldn't be found in the PATH, clean up
	if (!*cmd_path_out)
	{
		free_split(args);
		return (NULL);
	}
	// ✅ Everything is set: return the args for use in execve
	return (args);
}
