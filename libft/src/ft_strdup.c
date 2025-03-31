/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:36:20 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:16:05 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates sufficient memory for a copy of the string s,
 * 		  does the copy, and returns a pointer to it.
 * 		  The pointer may subsequently be used as an
 * 		  argument to the function free(3).
 * @param s The string to duplicate.
 * @return char* Pointer to the duplicated string.
 * 		   NULL if insufficient memory was available.
 */
char	*ft_strdup(const char *s)
{
	char	*s_dup;
	int		s_len;
	int		i;

	s_len = ft_strlen(s);
	s_dup = (char *)ft_calloc(s_len + 1, sizeof(char));
	if (!s_dup)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		s_dup[i] = s[i];
		i++;
	}
	return (s_dup);
}
