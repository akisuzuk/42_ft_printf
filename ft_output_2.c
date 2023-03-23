/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:26:39 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/23 15:31:11 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_percent(t_flag *info)
{
	info->putlen = 1;
	info->field = (info->field <= info->putlen ? 0 : info->field - info->putlen);
	if (!info->flag[0] && !info->flag[1])
		ft_putchar_rep(' ', 1, info->field);
	ft_putchar_rep('0', 1, (info->flag[1] && !info->flag[0]) ? info->field : 0);
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
	ft_putchar_rep('0', 1, info->acc + ((info->flag[1] && !info->flag[0]) ? info->field : 0));
	if (num)
	{
		if (info->specifier == 5)
			ft_putnbr_base((num < 0 ? -1 : 1) * num, "0123456789");
		else if (info->specifier == 6)
			ft_putnbr_base((num < 0 ? -1 : 1) * num, "0123456789abcdef");
		else
			ft_putnbr_base((num < 0 ? -1 : 1) * num, "0123456789ABCDEF");
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
	ft_putchar_rep('0', 1, info->acc + ((info->flag[1] && !info->flag[0]) ? info->field : 0));
	if (num)
		ft_putnbr_fd((num < 0 ? -1 : 1) * num, 1);
	if (info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
}
