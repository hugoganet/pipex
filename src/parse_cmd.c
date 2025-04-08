/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:16:13 by hganet            #+#    #+#             */
/*   Updated: 2025/04/08 13:22:55 by hganet           ###   ########.fr       */
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
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		joined = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(joined, cmd);
		free(joined);
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
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

	args = ft_split(cmd_str, ' ');
	if (!args || !args[0])
	{
		free_split(args);
		return (NULL);
	}
	*cmd_path_out = get_cmd_path(args[0], envp);
	if (!*cmd_path_out)
	{
		free_split(args);
		return (NULL);
	}
	return (args);
}
