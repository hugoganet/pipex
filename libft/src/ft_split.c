/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:03:59 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:12:25 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_substring(char const *s, char c, int s_len)
{
	int	i;
	int	n;

	if (!s[0] || s_len == 0)
		return (0);
	i = 0;
	n = 0;
	while (i < s_len && s[i])
	{
		if (s[i] != c)
		{
			n++;
			while (i < s_len && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (n);
}

static void	free_memory(char **result, int arr_index)
{
	while (arr_index >= 0)
		free(result[arr_index--]);
	free(result);
}

static int	allocate_memory(char ***result, int arr_index, int len)
{
	(*result)[arr_index] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!(*result)[arr_index])
	{
		free_memory(*result, arr_index - 1);
		*result = NULL;
		return (0);
	}
	return (1);
}

static int	copy_substring(char **result, char const *s, char c, int s_len)
{
	int	i;
	int	len;
	int	arr_index;

	arr_index = 0;
	i = 0;
	while (i < s_len && s[i])
	{
		if (s[i] == c)
			while (s[i] == c)
				i++;
		len = 0;
		while (i + len < s_len && s[i + len] && s[i + len] != c)
			len++;
		if (len > 0)
		{
			if (!allocate_memory(&result, arr_index, len))
				return (0);
			ft_strlcpy(result[arr_index++], &s[i], len + 1);
			i += len;
		}
	}
	return (1);
}

/**
 * @brief Allocates (with malloc(3)) and returns
 * 		  an array of strings obtained by splitting 's'
 * 		  using the character 'c' as a delimiter.
 * 		  The array must end with a NULL pointer.
 * @param s The string to be split
 * @param c The delimiter character
 * @return The array of new strings resulting from the split.
 * 		   NULL if the allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		n_substring;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
		return ((char **)ft_calloc(1, sizeof(char *)));
	n_substring = count_substring(s, c, ft_strlen(s));
	result = (char **)ft_calloc((n_substring + 1), sizeof(char *));
	if (!result)
		return (NULL);
	if (!copy_substring(result, s, c, ft_strlen(s)))
		return (NULL);
	return (result);
}
