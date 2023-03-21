/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_ele.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:28:55 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/21 23:32:47 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_percent(t_flag *info)
{
	info->putlen = 1;
	info->field = (info->field <= info->putlen ? 0 : info->field - info->putlen);
	// フラグが特にない場合
	if (!info->flag[0] && !info->flag[1])

}

void	ft_unsigned_print(va_list *arg, t_flag *info)
{

}

int ft_get_digit(int num)
{
	int	digit;

	if (num == 0)
		return (1);
	digit = 0;
	while (num)
	{
		digit++;
		num /= 10;
	}
	return (digit);
}

void	ft_get_putlen(t_flag *info, int num)
{
	// ↓一行目から謎コード
	//info->flag[0] = info->flag[0] && (info->acc == -1);
	if(info->specifier == 3 || info->specifier == 4)
	{
		info->putlen = ft_get_digits(num);
		// 論理演算子を算術演算子で処理すると1(True)か0(False)が返るんだな
		info->acc = (info->acc <= info->putlen ? \
					(num == 0 && info->acc) : info->acc = info->putlen);

//---KOKOMADE---SUSUNDA---KOKOMADE---SUSUNDA---KOKOMADE---SUSUNDA---
	}
}

void ft_int_print(va_list *arg, t_flag *info)
{
	int num;

	num = va_arg(*arg, int);
	// info->putlenに数字部分の桁数、info->fieldに空白部分の桁数を格納
	ft_get_putlen(info, num);
	if(!info->flag[0] && !info->flag[1])
		// field分だけ空白埋める
		ft_putchar_rep('', 1, info->field);
	ft_put_plus_minus(info, num);
	// 0埋めフラグあれば対応。なければflag[1]が0だから何もしないかな？
	ft_putchar_rep('0', 1, info->acc +
				(info->flag[0] && info->flag[1]) ? info->field : 0);
	if (num)
		ft_putnbr_fd((num < 0 ? -1 : 1) * num, 1, 0);
	if (info->flag[0])
		ft_putchar_rep('', 1, info->field);
}

void	ft_pointer_print(va_list *arg, t_flag *info)
{

}

void	ft_string_print(va_list *arg, t_flag *info)
{

}

void	ft_char_print(va_list *arg, t_flag *info)
{

}

// まさかの指定子がなかったら、そのままformatの中身を出力してしまう
int	ft_non_specifier(const char **p, const char **format, t_flag *info)
{
	if (!**format)
		return (-1);
	info->putlen = *format - *p;
	write(1, *p, info->putlen);
	//return (info->putnum + info->putlen);
	return (info->putlen);
}
