/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:15:01 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/25 12:37:52 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_rep(char c, int fd, int rep)
{
	int	i;

	i = 0;
	while (i < rep)
	{
		write(fd, &c, 1);
		i++;
	}
}

int	ft_get_digit(int num, int base)
{
	int	digit;
	int	basenum;

	if (num == 0)
		return (1);
	if (base == 3 || base == 4 || base == 5)
		basenum = 10;
	else
		basenum = 16;
	digit = 0;
	while (num)
	{
		num /= basenum;
		digit++;
	}
	return (digit);
}

void	if_puxx(t_flag *info, int num)
{
	info->putlen = ft_get_digit(num, info->specifier);
	if (info->acc <= info->putlen)
		info->acc = (num == 0 && info->acc);
	else
		info->acc = info->acc - info->putlen;
	info->putlen += info->acc + 2 * (num != 0 && info->specifier != 2);
	if (info->field <= info->putlen)
		info->field = 0;
	else
		info->field = info->field - info->putlen;
}

void	ft_get_putlen(t_flag *info, int num)
{
	info->flag[1] = (info->flag[1] && info->acc == -1);
	if (info->specifier == 3 || info->specifier == 4)
	{
		info->putlen = ft_get_digit(num, info->specifier);
		if (info->acc <= info->putlen)
			info->acc = (num == 0 && info->acc);
		else
			info->acc = info->acc - info->putlen;
		info->putlen += info->acc + (num < 0);
		if (info->field <= info->putlen)
			info->field = 0;
		else
			info->field = info->field - info->putlen;
	}
	else if (info->specifier == 2 || (info->specifier >= 5 \
									&& info->specifier <= 7))
	{
		if_puxx(info, num);
	}
}
