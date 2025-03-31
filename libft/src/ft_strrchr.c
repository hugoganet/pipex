/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:23:20 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:14:23 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the last occurrence of c
 * 				(converted to a char) in the string s.
 * @param s The string to search.
 * @param c The character to search for.
 * @return A pointer to the located character,
 * 				 or NULL if the character does not appear in the string.
*/
char	*ft_strrchr(const char *s, int c)
{
	int		src_len;
	char	c_char;
	int		i;

	src_len = ft_strlen(s);
	c_char = c;
	i = src_len;
	while (i >= 0)
	{
		if (s[i] == c_char)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
