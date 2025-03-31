/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:45:37 by hganet            #+#    #+#             */
/*   Updated: 2025/02/27 15:52:58 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int ft_putstr_len_fd(char *str, int fd);
int ft_putnbr_len_fd(int n, int fd);
int ft_putunbr_len_fd(unsigned int n, int fd);
int ft_putnbr_base_len_fd(unsigned int n, char *base, int fd);
int handle_pointer_format(uintptr_t ptr, int fd);

void process_arg(char format, va_list args, int *len)
{
	if (format == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		(*len)++;
	}
	if (format == '%')
	{
		ft_putchar_fd('%', 1);
		(*len)++;
	}
	if (format == 's')
		*len += ft_putstr_len_fd(va_arg(args, char *), 1);
	if (format == 'i' || format == 'd')
		*len += ft_putnbr_len_fd(va_arg(args, int), 1);
	if (format == 'u')
		*len += ft_putunbr_len_fd(va_arg(args, unsigned int), 1);
	if (format == 'p')
		*len += handle_pointer_format((uintptr_t)va_arg(args, void *), 1);
	if (format == 'x')
		*len += ft_putnbr_base_len_fd(va_arg(args, int), "0123456789abcdef", 1);
	if (format == 'X')
		*len += ft_putnbr_base_len_fd(va_arg(args, int), "0123456789ABCDEF", 1);
}

int is_valid_format(char c)
{
	if ((
			c == 'c' || c == 's' || c == 'd' || c == 'i' || c == 'p' || c == 'u' || c == 'x' || c == 'X' || c == '%'))
		return (1);
	return (0);
}

int ft_printf(const char *format, ...)
{
	int i;
	int len;
	va_list args;

	va_start(args, format);
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] && is_valid_format(format[i + 1]))
			process_arg(format[++i], args, &len);
		else
		{
			write(1, &format[i], 1);
			len++;
		}
		i++;
	}
	if (len < 0)
		return (-1);
	va_end(args);
	return (len);
}
