/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:24:24 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:10:15 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates memory for an array of nmemb elements of size bytes each
 * 		  and returns a pointer to the allocated memory.
 * 		  The memory is set to zero. 
 * 		  If nmemb or size is 0, then calloc() returns either NULL,
 * 		  or a unique pointer value that can later be successfully passed to free().
 * @param nmemb Number of elements.
 * @param size Size of each element.
 * @return void* Pointer to the allocated memory.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	char	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	total_size = nmemb * size;
	ptr = (char *)malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
