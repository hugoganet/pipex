/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:39:20 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:10:56 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	get_arr_size(long int long_n)
{
	long int	arr_size;

	arr_size = 1;
	if (long_n < 0)
	{
		long_n *= -1;
		arr_size++;
	}
	while (long_n > 9)
	{
		long_n /= 10;
		arr_size++;
	}
	return (arr_size);
}

/**
 * @brief Allocates (with malloc(3)) and returns a string
 * 		  representing the integer received as an argument.
 * @param n the integer to convert.
 * @return The string representing the integer.
 * 		   NULL if the allocation fails.
 */
char	*ft_itoa(int n)
{
	char		*result;
	long int	long_n;
	long int	arr_size;
	long int	i;

	long_n = n;
	arr_size = get_arr_size(long_n);
	result = (char *)ft_calloc(arr_size + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (long_n < 0)
	{
		long_n *= -1;
		result[0] = '-';
	}
	i = arr_size - 1;
	while (long_n > 9)
	{
		result[i] = (long_n % 10) + '0';
		i--;
		long_n /= 10;
	}
	result[i--] = long_n + '0';
	return (result);
}
