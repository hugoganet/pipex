/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:50:19 by hganet            #+#    #+#             */
/*   Updated: 2024/11/21 10:54:53 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fill a byte string with a byte value
 * @param s The string to fill
 * @param c The byte value to fill the string with
 * @param n The number of bytes to fill
 * @return A pointer to the filled string
 */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = c;
	return ((char *)s);
}
/*
int	main(void)
{
	char	s[10];

	ft_memset(s, 'H', 5);
	s[5] = '\0';
	printf("%s\n", s);
	return (0);
}
*/
