/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:28:55 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/23 15:30:29 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	ft_pointer_print(va_list *arg, t_flag *info)
{
	unsigned long long	num;

	num = (unsigned long long)va_arg(*arg, void *);
	if (num == 0)
	{
		info->acc = (info->acc == -1 ? 1 : info->acc);
		info->putlen = 2 + info->acc;
		info->field = ((info->field <= info->putlen) ? 0 : info->field - info->putlen);
	}
	else
		ft_get_putlen(info, num);
	if (!info->flag[0] && !info->flag[1])
		ft_putchar_rep(' ', 1, info->field);
	write(1, "0x", 2);
	ft_putchar_rep('0', 1, info->acc + ((info->flag[1] && !info->flag[0]) ? info->field : 0));
	if (num)
		ft_putnbr_base((num < 0 ? -1 : 1) * num, "0123456789abcdef");
	if (info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
}

static	void	ft_string_print(va_list *arg, t_flag *info)
{
	char	*s;
	int		n;

	s = (char *)va_arg(*arg, char *);
	if (info->acc < 0)
		info->acc = INT_MAX;
	info->putlen = (int)ft_strlen(s);
	info->field = ((info->field <= info->putlen) ? 0 : (info->field - info->putlen));
	if (!info->flag[0])
		ft_putchar_rep((info->flag[1] ? ' ' : '0'), 1, info->field);
	n = info->putlen - (info->acc > 0);
	write(1, &s, n);
	if (info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
}

static	void	ft_char_print(va_list *arg, t_flag *info)
{
	char	c;

	c = (char)va_arg(*arg, int);
	info->putlen = 1;
	info->field = ((info->field <= info->putlen) ? 0 : (info->field - info->putlen));
	if (!info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
	write(1, &c, 1);
	if (info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
}

static	int	ft_non_specifier(const char **p, const char **fmt, t_flag *info)
{
	if (!**fmt)
		return (-1);
	info->putlen = *fmt - *p;
	write(1, *p, info->putlen);
	return (info->putlen);
}

int	ft_output(const char **p, const char **fmt, va_list *arg, t_flag *info)
{
	if (info->specifier == -1)
		return (ft_non_specifier(p, fmt, info));
	(*fmt)++;
	if (info->specifier == 0)
		ft_char_print(arg, info);
	else if (info->specifier == 1)
		ft_string_print(arg, info);
	else if (info->specifier == 2)
		ft_pointer_print(arg, info);
	else if (info->specifier == 3 || info->specifier == 4)
		ft_int_print(arg, info);
	else if (info->specifier >= 5 && info->specifier <= 7)
		ft_unsigned_print(arg, info);
	else
		ft_print_percent(info);
	return (info->putlen + info->field);
}
