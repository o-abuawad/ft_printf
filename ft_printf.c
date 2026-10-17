/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabu-awa <oabu-awa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 15:10:19 by oabu-awa          #+#    #+#             */
/*   Updated: 2026/10/17 15:25:20 by oabu-awa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_val(char f, va_list *arg)
{
	if (f == 'c')
		return (ft_putchar(va_arg(*arg, int)));
	if (f == 's')
		return (ft_putstr(va_arg(*arg, char *)));
	if (f == 'd' || f == 'i')
		return (ft_putnbr(va_arg(*arg, int)));
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
