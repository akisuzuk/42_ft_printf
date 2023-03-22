/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_ele.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:28:55 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/22 23:50:31 by akisuzuk         ###   ########.fr       */
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

void	ft_print_percent(t_flag *info)
{
	info->putlen = 1;
	info->field = (info->field <= info->putlen ? 0 : info->field - info->putlen);
	// フラグが特にない場合
	if (!info->flag[0] && !info->flag[1])
		ft_putchr_rep('', 1, info->field);
	ft_putchr_rep('0', 1, (info->flag[1] && !info->flag[]) ? info->field : 0);
	write(1, '%%', 1);
	if (info->flag[0])
		ft_putchr_rep('', 1, info->field);
}

int ft_get_digit(int num, int base)
{
	int	digit;
	int basenum;

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

// info->putlenに数字部分の桁数、info->fieldに空白部分の桁数を格納
void	ft_get_putlen(t_flag *info, int num)
{
	// 0埋めフラグの中身にTrue/falseを格納
	// なぜ精度accのtrue/falseが絡んで来るんだ？？
	info->flag[1] = info->flag[1] && (info->acc == -1);
	if(info->specifier == 3 || info->specifier == 4)
	{
		info->putlen = ft_get_digit(num, info->specifier);
		// 論理演算子を算術演算子で処理すると1(True)か0(False)が返るんだな
		// accの精度ってのは出力すべき"最低"桁数なので
		// acc > putlenだとputlen分だけ削ってピッタリにする
		info->acc = (info->acc <= info->putlen ? \
					(num == 0 && info->acc) : info->acc - info->putlen);
		// accの値に応じでputlenを補正
		info->putlen += info->acc + (num < 0);
		info->field = (info->field <= info->putlen ? 0 : info->field - info->putlen);
	}
	else if (info->specifier == 2 || (info->specifier >= 5 && info->specifier <= 7))
	{
		info->putlen = ft_get_digit(num, info->specifier);
		info->acc = (info->acc <= info->putlen ?
					(num ==0 && info->acc) : info->acc - info->putlen);
		// 16進数の場合先頭にoxをつけるので、該当する場合その文字数を確保
		info->putlen += info->acc + 2 * (num != 0 && info->specifier != 2);
		info->field = (info->field <= info->putlen ? 0 : info->field - info->putlen);
	}
}

// putnbrがunsigned int対応じゃないのでデバッグ必要かも
void	ft_unsigned_print(va_list *arg, t_flag *info)
{
	unsigned int num;

	num = va_arg(*arg, unsigned int);
	ft_get_putlen(info, num);
	if (!info->flag[0] && !info->flag[1])
		ft_putchr_rep(' ', 1, info->field);
	ft_putchr_rep('0', 1, info->acc +
				(info->flag[1] && !info->flag[0]) ? info->field : 0);
	if (num)
		// そもそもunsignedにマイナスないから三項演算子の判定いらないかも
		if(info->specifier == 5)
			ft_putnbr_base((num < 0 ? -1 : 1) * num, "0123456789");
		else if (info->specifier == 6)
			ft_putnbr_base((num < 0 ? -1 : 1) * num, "0123456789abcdef");
		else
			ft_putnbr_base((num < 0 ? -1 : 1) * num, "0123456789ABCDEF");
	if (info->flag[0])
		ft_putchr_rep(' ', 1, info->field);
}

void ft_int_print(va_list *arg, t_flag *info)
{
	int num;

	num = va_arg(*arg, int);
	// info->putlenに数字部分の桁数、info->fieldに空白部分の桁数を格納
	ft_get_putlen(info, num);
	if (!info->flag[0] && !info->flag[1])
		// field分だけ空白埋める
		ft_putchr_rep(' ', 1, info->field);
	if (num < 0)
		write(1, '-', 1);
	// 0埋めフラグあれば対応。なければflag[1]が0だから何もしないかな？
	ft_putchr_rep('0', 1, info->acc +
				(info->flag[1] && !info->flag[0]) ? info->field : 0);
	if (num)
		// この書き方だとINT_MINがぶっ飛ぶ気がするので修正
		ft_putnbr_fd((num < 0 ? -1 : 1) * num, 1, 0);
	if (info->flag[0])
		ft_putchr_rep(' ', 1, info->field);
}

void	ft_pointer_print(va_list *arg, t_flag *info)
{
	// ここなぜlong longなのか確認
	unsigned long long num;

	num = (unsigned long long)var_arg(*arg, void *);
	// nullポインタ対策
	if (num == 0)
	{
		info->acc = (info->acc == -1 ? 1 : info->acc);
		// 先頭のoxは手動なのでその2文字分を足してやる
		info->putlen = 2 + info->acc;
		info->field = (info->field <= info->putlen ? 0 : info->field - info->putlen);
	}
	else
		ft_get_putlen(info, num);
	if (!info->flag[0] && !info->flag[1])
		ft_putchr_rep(' ', 1, info->field);
	write(1, '0x', 2);
	ft_putchr_rep('0', 1, info->acc + (info->flag[1] && !info->flag[0] ? info->field : 0));
	if (num)
		ft_putnbr_base((num < 0 ? -1 : 1) * num, "0123456789abcdef");
	// フラグがマイナスの場合
	if (info->flag[0])
		ft_putchr_rep(' ', 1, info->field);
}
//21:00
// 26:08にft_set_t_string
void	ft_string_print(va_list *arg, t_flag *info)
{
	char	*s;
	int		n;

	s = (char *)va_arg(*arg, int);
	if (info->acc < 0)
		info->acc = INT_MAX;
	//n = ft_set_string(arg, info, &s);
	//if (info->putlen > info->acc)
	//	info->putlen -= n;
	info->putlen = ft_strlen(s);
	info->field = (info->field <= info->putlen ? 0 : info->field - info->putlen);
	if (!info->flag[0])
		ft_putchr_rep((info->flag[1] ? ' ' : '0', 1, info->field));
	// あーn周り怪しいな...
	n = info->putlen - (info->acc > 0);
	write(1, &s, n);
	if (info->flag[0])
		ft_putchr_rep(' ', 1, info->field);
}

// field→出力する空白(もしくは0)の数
// acc→出力する最"大"桁数。なので数字と違って途中で切れる可能性がある
void	ft_char_print(va_list *arg, t_flag *info)
{
	char c;

	c = (char)va_arg(*arg, int);
	// あれっ長さ1って自明だよね...
	info->putlen = 1;
	info->field = (info->field <= info->putlen ? 0 : info->field - info->putlen);
	// マイナスフラグなければ空白で0埋め
	if (!info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
	write(1, &c, 1);
	if (info->flag[0])
		ft_putchar_rep(' ', 1, info->field);
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
