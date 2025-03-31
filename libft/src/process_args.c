/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoganet <hugoganet@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:48:53 by hganet            #+#    #+#             */
/*   Updated: 2025/02/27 15:49:49 by hugoganet        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_putstr_len_fd(char *str, int fd)
{
	int	len;

	if (fd < 0)
		return (0);
	if (!str)
		str = "(null)";
	len = 0;
	while (str[len])
	{
		write(fd, &str[len], 1);
		len++;
	}
	return (len);
}

int	ft_putnbr_len_fd(int n, int fd)
{
	int		len;
	char	c;

	if (fd < 0)
		return (0);
	len = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (n < 0)
	{
		len += write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		len += ft_putnbr_len_fd(n / 10, fd);
	c = n % 10 + '0';
	len += write(fd, &c, 1);
	return (len);
}

int	ft_putunbr_len_fd(unsigned int n, int fd)
{
	int		len;
	char	c;

	if (fd < 0)
		return (0);
	len = 0;
	if (n >= 10)
		len += ft_putunbr_len_fd(n / 10, fd);
	c = n % 10 + '0';
	len += write(fd, &c, 1);
	return (len);
}

int	ft_putnbr_base_len_fd(unsigned int n, char *base, int fd)
{
	unsigned int	base_len;
	int				len;

	if (fd < 0)
		return (0);
	len = 0;
	base_len = ft_check_base(base);
	if (!base_len)
		return (0);
	if (n >= base_len)
		len += ft_putnbr_base_len_fd(n / base_len, base, fd);
	len += write(fd, &base[n % base_len], 1);
	return (len);
}

int	handle_pointer_format(uintptr_t ptr, int fd)
{
	int		len;
	int		i;
	char	*hex_base;
	char	buffer[16];

	if (fd < 0)
		return (0);
	len = 0;
	if (ptr == 0)
		return (ft_putstr_len_fd("(nil)", fd));
	i = 0;
	hex_base = "0123456789abcdef";
	len += ft_putstr_len_fd("0x", fd);
	while (ptr > 0)
	{
		buffer[i++] = hex_base[ptr % 16];
		ptr /= 16;
	}
	while (--i >= 0)
		len += write(fd, &buffer[i], 1);
	return (len);
}
