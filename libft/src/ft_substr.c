/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:52:33 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:15:37 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_substring(char const *s,
							char *substr,
							unsigned int start, size_t len)
{
	unsigned int	i;

	i = 0;
	while (len != 0)
	{
		substr[i++] = s[start++];
		len--;
	}
}

/**
 * @brief Allocates (with malloc(3)) and returns a substring
 *		  from the string ’s’
 *		  The substring begins at index ’start’ and is of
 *		  maximum size ’len’
 * @param s The string from which to create the substring.
 * @param start  The start index of the substring in the
 *				 string ’s’
 * @param len The maximum length of the substring
 * @return The substring. NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		substr = ft_strdup("");
		if (!substr)
			return (NULL);
		return (substr);
	}
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)ft_calloc((len + 1), sizeof(char));
	if (!substr)
		return (NULL);
	copy_substring(s, substr, start, len);
	return (substr);
}
