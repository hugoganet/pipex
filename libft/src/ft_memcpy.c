/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:58:01 by hganet            #+#    #+#             */
/*   Updated: 2025/01/22 16:20:46 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The memcpy() function copies n bytes from memory area src
 * 		  to memory area dest.
 * 		  The memory areas must not overlap.
 * 		  Use memmove(3) if the memory areas do overlap.
 * @param dest The pointer to the destination string.
 * @param src The pointer to the source string.
 * @param n The number of bytes to be copied.
 * @return The original value of dest.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return ((char *)dest);
}
