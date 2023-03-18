/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:16:20 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/02 19:16:20 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//--------------------------------------
// 課題ではとりあえず
// %c, %s, %p, %d, %i, %u, %x, %X, %%
// に対応させられればok
// 出力の書式は
// %[フラグ][最小フィールド幅].[精度][長さ修飾子][変換指定子]
// で示されるけど、今回長さ修飾子は不要
// フラグは-と0と*だけ対応すればok
//
// ft_substr_to_num関数、よくできてんな。。。普通にすごすぎ
// 動画05の17:00くらいからのエラー処理も対策
//--------------------------------------

#include "ft_printf.h"
//include "libftprintf.a"

int		ft_isdigit(int c);	// ライブラリ使うとはいえプロトタイプ宣言は要るっぽい
int		ft_strchr_order(const char *s, int c);
void	ft_proc_per(const char **p, const char **format, int *i, va_list *arg);
void	ft_print_str(const char **p, const char **format, int *i);
int		ft_printf(const char *format, ...);

int	output(const char **p, const char **format, va_list *arg, t_flag *info)
{
	if (info->specifier == -1)
		return (ft_non_specifier(p, format, info));
	(*format)++;
//---KOKOMADE---SUSUNDA---KOKOMADE---SUSUNDA---KOKOMADE---SUSUNDA---
}

int	ft_substr_to_num(const char **format, va_list *arg, int mode, t_flag *info)
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
int		ft_strchr_order(const char *s, int c)
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

void	ft_init_flag(t_flag *s, int i)
{
	s->flag[0] = 0;
	s->flag[1] = 0;
	s->flag[2] = 0;
	//s->flag[3] = 0;
	//s->flag[4] = 0;
	s->field = -1;
	s->acc = -1;
	//s->modifier = -1;
	s->specifier = -1;
	s->putnum = (i < 0 ? 0 : i);
	s->putlen = 0;
}

void	ft_proc_per(const char **p, const char **format, int *i, va_list *arg)
{
	int		num;
	t_flag	info;

	(*format)++;
	ft_init_flag(&info, *i);
	// フラグがあるなら%の後にすぐ出てくるから、num >= 0じゃなかったら即刻ループ終了か。SUGEEE
	while ((num = ft_strchr_order("-0*", **format)) >= 0)
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
	num = output(p, format, arg, &info);
	// ↓文字数iカウント。とはいえ複雑ではなく、フィールド幅の数字(指定なければ実際に吐き出された文字数)をそのまま足すだけか.
	//*i += *format - *p;
	//*i = ((*i == 0 || num >= 0) ? num : *i);
	*i += num; // あれっ三項演算子使わず普通にこれで良いのでは
}

void	ft_print_str(const char **p, const char **format, int *i)
{
	while (**format != '%' && **format)
		(*format)++;
	write(1, *p, *format - *p);
	*i += *format - *p;
}


// 第一引数を%まで読み込む→出力するって流れを作ってみたので、
// それを可変朝変数p = (char *)var_arg(arg, char *);と絡めて出力するのを実装していく
int		ft_printf(const char *format, ...)
{
	va_list		arg;	// argがこれ以降のva_startとかva_listの第一引数になる
	const char	*p;
	int			i;

	va_start(arg, format); // 第二引数には、プロトタイプ宣言の第一引数を設定
	i = 0;
	if (format == NULL)
		i = -1;
	while (i >= 0 && *format)
	{
		p = format;
		if (*p != '%')
			ft_print_str(&p, &format, &i);  // あれっなんでポインタにアドレスつけてる？
		else
			ft_proc_per(&p, &format, &i, &arg);
		format++;
	}

	// 第二引数以降を拾っていって格納してまとめて表示

	va_end (arg); // va_startとセット。可変長引数の処理を完了
	return (i);
}

// va系の挙動チェック用
// ft_printf("abc", "def", "ghi"); をぶッ込んで試す
// ft_printf("%d %c %s", "def", "ghi"); とかやってみたら第一引数に正規表現入っててループがおかしくなってしまった。。。
//int		ft_printf(const char *format, ...)
//{
//	const char	*p;
//	int			i;
//	va_list		arg;	// argがこれ以降のva_startとかva_listの第一引数になる
//
//	i = 0;
//	va_start(arg, format); // 第二引数には、プロトタイプ宣言の第一引数を設定
//	if (format == NULL)
//		i = -1;
//	printf("format=%s\n", format);
//	while (i >= 0 && *(++format))
//	{
//		printf("va_arg=%s\n", va_arg(arg, char *));
//		//format++;
//	}
//
//	// 第二引数以降を拾っていって格納してまとめて表示
//
//	va_end (arg); // va_startとセット。可変長引数の処理を完了
//	return (i);
//}

int main(int argc, char const * argv[])
{
	ft_printf("xxx%dyyy%c", 3, "def");
	//printf("c1=%c, c2=%c, i1=%d, i2=%d\n", 'a', 'z', 1, 9);
	//ft_printf("c1=%c, c2=%c, i1=%d, i2=%d\n", 'a', 'z', 1, 9);
	return 0;
}



	//p = (char *)var_arg(arg, char *);
	//d = (int)var_arg(arg, int);
	//c = (char)var_arg(arg, int);	// 読み込みは4バイトずつなのでcharを引っ張ってくる時もargの引数はintでずらした箇所を参照する
