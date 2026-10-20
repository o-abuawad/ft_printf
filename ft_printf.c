/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabu-awa <oabu-awa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 15:10:19 by oabu-awa          #+#    #+#             */
/*   Updated: 2026/10/20 17:10:20 by oabu-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putunsigned(unsigned int n)
{
	if (n >= 10)
		return (ft_putunsigned(n / 10) + ft_putchar('0' + (n % 10)));
	return (ft_putchar('0' + (n % 10)));
}

static int	dec_to_hex(unsigned long n, const char *base)
{
	if (n >= 16)
		return (dec_to_hex(n / 16, base) + write(1, &base[n % 16], 1));
	return (write(1, &base[n % 16], 1));
}

static int	check_val(char f, va_list *arg)
{
	if (f == 'c')
		return (ft_putchar(va_arg(*arg, int)));
	if (f == 's')
		return (ft_putstr(va_arg(*arg, char *)));
	if (f == 'd' || f == 'i')
		return (ft_putnbr(va_arg(*arg, int)));
	if (f == 'u')
		return (ft_putunsigned(va_arg(*arg, unsigned int)));
	if (f == 'x')
		return (dec_to_hex(va_arg(*arg, unsigned int), "0123456789abcdef"));
	if (f == 'X')
		return (dec_to_hex(va_arg(*arg, unsigned int), "0123456789ABCDEF"));
	if (f == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		printed;

	if (!format)
		return (-1);
	printed = 0;
	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				return (va_end(arg), -1);
			printed += check_val(*format, &arg);
		}
		else
			printed += ft_putchar(*format);
		format++;
	}
	va_end(arg);
	return (printed);
}
