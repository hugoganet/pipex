/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:55:55 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:14:18 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of the null-terminated string little
 * 		  in the string big, where not more than len characters are searched.
 * @param big The string to search.
 * @param little The string to search for.
 * @param len The maximum number of characters to search.
 * @return A pointer to the located character
 * 		  or NULL if the string is not found.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;

	if ((!big || !little) && len == 0)
		return (NULL);
	if (ft_strlen(big) < len)
		len = ft_strlen(big);
	i = 0;
	if (!little[i])
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && (i + j) < len)
			j++;
		if (!little[j])
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
