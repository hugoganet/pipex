/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hganet <hganet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:11:08 by hganet            #+#    #+#             */
/*   Updated: 2024/12/03 11:10:05 by hganet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* @brief Checks for an alphabetic character; in the standard "C" locale.
* @param c character to be checked
* @return The function returns zero if the character tests false 
* 				and returns non-zero if the character tests true.
*/
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
