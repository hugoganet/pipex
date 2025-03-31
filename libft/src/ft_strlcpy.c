/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:09:46 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:13:16 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies up to siz - 1 characters
 * 				from the NUL-terminated string src to dst,
 * 				NUL-terminating the result.
 * @param dst The destination string
 * @param src The source string
 * @param siz The size of the destination buffer
 * @return size_t The total length of the string it tried to create
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	unsigned int	i;

	if (siz > 0)
	{
		i = 0;
		while (i < siz - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
