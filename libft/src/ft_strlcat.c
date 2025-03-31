/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:16:47 by hganet            #+#    #+#             */
/*   Updated: 2025/02/27 15:43:20 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static int	min(int n1, int n2)
{
	if (n1 <= n2)
		return (n1);
	else
		return (n2);
} */

/**
 * @brief Appends the NUL-terminated string src to the end of dst.
 * 		  It will append at most (size - strlen(dst) - 1 bytes),
 * 		  NUL-terminating the result.
 * @param dst The destination string.
 * @param src The source string.
 * @param siz The size of the destination buffer.
 * @return The total length of the string it tried to create.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	int			j;
	size_t		i;
	size_t		dst_i_len;

	if (!dst && siz == 0)
		return (ft_strlen(src));
	i = 0;
	while (dst[i])
		i++;
	dst_i_len = i;
	j = 0;
	if (dst_i_len < siz)
	{
		while (i < siz - 1 && src[j])
			dst[i++] = src[j++];
		dst[i] = '\0';
	}
	if (dst_i_len < siz)
		return (ft_strlen(src) + dst_i_len);
	else
		return (ft_strlen(src) + siz);  
}
