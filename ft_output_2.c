/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:26:39 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/23 22:49:06 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_percent(t_flag *info)
{
	info->putlen = 1;
	if (info->field <= info->putlen)
		info->field = 0;
	else
		info->field -= info->putlen;
	if (!info->flag[0] && !info->flag[1])
		ft_putchar_rep(' ', 1, info->field);
	if (info->flag[1] && !info->flag[0])
		ft_putchar_rep('0', 1, info->field);
	else
		ft_putchar_rep('0', 1, 0);
	write(1, "%%", 1);
	if (info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
}

void	ft_unsigned_print(va_list *arg, t_flag *info)
{
	unsigned int	num;

	num = va_arg(*arg, unsigned int);
	ft_get_putlen(info, num);
	if (!info->flag[0] && !info->flag[1])
		ft_putchar_rep(' ', 1, info->field);
	if (info->flag[1] && !info->flag[0])
		ft_putchar_rep('0', 1, info->acc + info->field);
	else
		ft_putchar_rep('0', 1, info->acc);
	if (num)
	{
		if (info->specifier == 5)
			ft_putnbr_base(num, "0123456789");
		else if (info->specifier == 6)
			ft_putnbr_base(num, "0123456789abcdef");
		else
			ft_putnbr_base(num, "0123456789ABCDEF");
	}
	if (info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
}

void	ft_int_print(va_list *arg, t_flag *info)
{
	int	num;

	num = va_arg(*arg, int);
	ft_get_putlen(info, num);
	if (!info->flag[0] && !info->flag[1])
		ft_putchar_rep(' ', 1, info->field);
	if (num < 0)
		write(1, "-", 1);
	if (info->flag[1] && !info->flag[0])
		ft_putchar_rep('0', 1, info->acc + info->field);
	else
		ft_putchar_rep('0', 1, info->acc);
	if (num)
	{
		if (num < 0)
			ft_putnbr_fd(-num, 1);
		else
			ft_putnbr_fd(num, 1);
	}
	if (info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
}

void	ft_if_num_zero(t_flag *info)
{
	if (info->acc == -1)
		info->acc = 1;
	info->putlen = 2 + info->acc;
	if (info->field <= info->putlen)
		info->field = 0;
	else
		info->field -= info->putlen;
}

void	ft_pointer_print(va_list *arg, t_flag *info)
{
	unsigned long long	num;

	num = (unsigned long long)va_arg(*arg, void *);
	if (num == 0)
		ft_if_num_zero(info);
	else
		ft_get_putlen(info, num);
	if (!info->flag[0] && !info->flag[1])
		ft_putchar_rep(' ', 1, info->field);
	write(1, "0x", 2);
	if (info->flag[1] && !info->flag[0])
		ft_putchar_rep('0', 1, info->acc + info->field);
	else
		ft_putchar_rep('0', 1, info->acc);
	if (num)
		ft_putnbr_base(num, "0123456789abcdef");
	if (info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
}
