/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:58:28 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:14:29 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_is_set(char c, char const *set, size_t set_len)
{
	size_t	i;

	i = 0;
	while (i < set_len)
		if (set[i++] == c)
			return (1);
	return (0);
}

static void	get_flags_indexes(
								char const *s1,
								char const *set,
								size_t *flag1,
								size_t *flag2)
{
	size_t	i;
	size_t	s1_len;
	size_t	set_len;

	set_len = ft_strlen(set);
	s1_len = ft_strlen(s1);
	*flag1 = 0;
	*flag2 = s1_len;
	i = 0;
	while (check_is_set(s1[i], set, set_len))
		i++;
	*flag1 = i;
	if (i < s1_len)
	{
		i = s1_len - 1;
		while (i > 0 && check_is_set(s1[i], set, set_len))
			i--;
		*flag2 = i + 1;
	}
}

/**
 * @brief Allocates (with malloc(3))
 * 		  and returns a copy of 's1' with the characters specified
 * 		  in 'set' removed from the beginning and the end of the string.
 * @param s1 The string to be trimmed
 * @param set The reference set of characters to trim
 * @return The trimmed string. NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	flag1;
	size_t	flag2;

	if (!s1 || !set)
		return (NULL);
	get_flags_indexes(s1, set, &flag1, &flag2);
	result = (char *)ft_calloc((flag2 - flag1 + 1), sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s1[flag1], flag2 - flag1 + 1);
	return (result);
}
