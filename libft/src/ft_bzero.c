/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:48:07 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:10:19 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The bzero() function writes n zeroed bytes to the string s.
 * 				If n is zero, bzero() does nothing.
 * @param s The pointer to the string to be zeroed.
 * @param n The number of bytes to be zeroed.
 * @return void
 */
void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = '\0';
}
