/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:04:06 by hganet            #+#    #+#             */
/*   Updated: 2024/11/12 17:05:38 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converts an upper-case letter to the corresponding lower-case letter.
 * @param c The character to convert.
 * @return The corresponding lower-case letter.
 */
int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	else
		return (c);
}
