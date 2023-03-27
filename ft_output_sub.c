/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:15:01 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/27 22:57:15 by akisuzuk         ###   ########.fr       */
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

int	digit_count(long long num_ll, unsigned long long num_ull, long long basenum)
{
	int	digit;

	digit = 0;
	if (num_ll != 0)
	{
		while (num_ll)
		{
			num_ll /= basenum;
			digit++;
		}
	}
	if (num_ull != 0)
	{
		while (num_ull)
		{
			num_ull /= basenum;
			digit++;
		}
	}
	return (digit);
}

int	ft_get_digit(long long num_ll, unsigned long long num_ull, int base)
{
	int			digit;
	long long	basenum;

	if (num_ll == 0 && num_ull == 0)
		return (1);
	if (base == 3 || base == 4 || base == 5)
		basenum = 10;
	else
		basenum = 16;
	digit = digit_count(num_ll, num_ull, basenum);
	return (digit);
}

void	if_puxx(t_flag *info, unsigned long long num_ull)
{
	info->putlen = ft_get_digit(0, num_ull, info->specifier);
	if (info->acc <= info->putlen)
		info->acc = (num_ull == 0 && info->acc > 0);
	else
		info->acc = info->acc - info->putlen;
	info->putlen += info->acc + 2 * (num_ull != 0 && info->specifier == 2);
	if (info->field <= info->putlen)
		info->field = 0;
	else
		info->field = info->field - info->putlen;
}

void	ft_get_putlen(t_flag *info, long long num_ll,
						unsigned long long num_ull)
{
	info->flag[1] = (info->flag[1] && info->acc == -1);
	if (info->specifier == 3 || info->specifier == 4)
	{
		info->putlen = ft_get_digit(num_ll, 0, info->specifier);
		if (info->acc <= info->putlen)
			info->acc = (num_ll == 0 && info->acc > 0);
		else
			info->acc = info->acc - info->putlen;
		info->putlen += info->acc + (num_ll < 0);
		if (info->field <= info->putlen)
			info->field = 0;
		else
			info->field = info->field - info->putlen;
	}
	else if (info->specifier == 2 || (info->specifier >= 5 \
									&& info->specifier <= 7))
	{
		if_puxx(info, num_ull);
	}
}
