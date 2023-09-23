/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungmiho <jungmiho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:35:26 by jungmiho          #+#    #+#             */
/*   Updated: 2023/09/23 21:15:53 by jungmiho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	len;

	if (s == 0)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = 0;
	while (*s != '\0')
	{
		ft_putchar(*s);
		s++;
		len++;
	}
	return (len);
}

int	return_len_by_placeholder(char ch, va_list arg_ptr)
{
	int	len;

	len = 0;
	if (ch == 'c')
		len += ft_putchar(va_arg(arg_ptr, int));
	else if (ch == 's')
		len += ft_putstr(va_arg(arg_ptr, char *));
	//else if (ch == 'd' || ch == 'i')
	//	len += ft_putnbr(va_arg(arg_ptr, int));
	//else if (ch == 'u')
	//	len += ft_putnbr_unsigned_int(va_arg(arg_ptr, unsigned int));
	//else if (ch == 'x' || ch == 'X')
	//	len += ft_puthex(va_arg(arg_ptr, unsigned int), ch);
	//else if (ch == 'p')
	//{
	//	len += ft_putstr("0x");
	//	len += ft_putaddr(va_arg(arg_ptr, unsigned long long));
	//}
	//else if (ch == '%')
	//{
	//	write(1, "%", 1);
	//	len = 1;
	//}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	char	ch;
	va_list	arg_ptr;

	len = 0;
	va_start(arg_ptr, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			len += return_len_by_placeholder(*format, arg_ptr);
		}
		else
		{
			ch = *format;
			if (write(1, &ch, 1) == -1)
				return (-1);
			len++;
		}
		format++;
	}
	va_end(arg_ptr);
	return (len);
}
