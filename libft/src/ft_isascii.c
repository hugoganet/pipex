/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_isascii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:41:15 by hganet            #+#    #+#             */
/*   Updated: 2024/11/12 16:48:44 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief The isascii() function tests for an ASCII character,
 * 				which is any character between 0 and octal 0177 inclusive.
 * @param c The character to test
 * @return The function returns zero if the character tests false
 * 				 and returns non-zero if the character tests true.
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
