/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:52:03 by hganet            #+#    #+#             */
/*   Updated: 2025/03/31 14:56:25 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Frees a null-terminated array of strings.
 *
 * This function is typically used to free the result of a function like ft_split,
 * where the result is a dynamically allocated array of dynamically allocated strings.
 *
 * @param arr The null-terminated array of strings to free.
 */
void free_split(char **arr)
{
	int i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * @brief Closes all open file descriptors in the t_pipex struct.
 *
 * Should be called in the parent process after forking,
 * to cleanly close unused file descriptors.
 *
 * @param px Pointer to the t_pipex structure.
 */
void close_fds(t_pipex *px)
{
	close(px->infile);
	close(px->outfile);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
}
