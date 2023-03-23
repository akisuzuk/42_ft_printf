/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_per.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:30:32 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/23 11:41:59 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_substr_to_num(const char **format, va_list *arg, int mode, t_flag *info)
{
	int		num;

	num = -1;
	if (**format == '*')
	{
		num = va_arg(*arg, int);
		if (num < 0 && !mode) // フィールド幅判定の時はmode=0なのでこのif文は必ず入る。精度の時は入らない
		{
			num *= -1;
			info -> flag[0] = 1; // -フラグだけはformatの中でなく、*の中に格納して参照させることが可能
		}
		else if (num < 0)
			num = -1;
		(*format)++;
	}
	else if (mode || ft_isdigit(**format)) // おーlibft来たね！
	{
		num = 0;
		while (ft_isdigit(**format))
			num = num * 10 + (*((*format)++) - '0');
	}
	return (num);
}

// 終端文字はサーチしなくてok
// 一応動画05の24分くらいで解説あり
static int	ft_strchr_order(const char *s, int c)
{
	char	char_c;
	int		order;

	char_c = (char)c;
	order = 0;
	while (s[order])
	{
		if (s[order] == char_c)
			return (order);
		order++;
	}
	//if (char_c == '\0' && *s == char_c)
	//	return ((char *)s);
	return (-1);
}

static void	ft_init_flag(t_flag *s)
{
	s->flag[0] = 0;
	s->flag[1] = 0;
	//s->flag[2] = 0;
	//s->flag[3] = 0;
	//s->flag[4] = 0;
	s->field = -1;
	s->acc = -1;
	//s->modifier = -1;
	s->specifier = -1;
	//s->putnum = (i < 0 ? 0 : i);
	s->putlen = 0;
}

void	ft_proc_per(const char **p, const char **format, int *i, va_list *arg)
{
	int		num;
	t_flag	info;

	(*format)++;
	ft_init_flag(&info);
	// フラグがあるなら%の後にすぐ出てくるから、num >= 0じゃなかったら即刻ループ終了か。SUGEEE
	// 一応、解説動画だと"#0- +"の順番でしたね
	while ((num = ft_strchr_order("-0", **format)) >= 0)
	{
		info.flag[num] = 1;
		(*format)++;	// これ、別に値を参照するわけじゃないからカッコいらないと思うんだが(あとで検証)
	}
	// フィールド幅を格納
	info.field = ft_substr_to_num(format, arg, 0, &info);
	// 精度を格納
	if (**format == '.')
	{
		(*format)++;
		info.acc = ft_substr_to_num(format, arg, 1, &info); // あーmodeを0/1でスイッチするんだね。イイネ
	}
	// 変換指定子を格納
	info.specifier = ft_strchr_order("cspdiuxX%", **format);
	// やっと格納
	num = ft_output(p, format, arg, &info);
	// ↓文字数iカウント。とはいえ複雑ではなく、フィールド幅の数字(指定なければ実際に吐き出された文字数)をそのまま足すだけか.
	//*i += *format - *p;
	//*i = ((*i == 0 || num >= 0) ? num : *i);
	*i += num; // あれっ三項演算子使わず普通にこれで良いのでは
}
