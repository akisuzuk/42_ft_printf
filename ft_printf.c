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
// ↑と思ってたら解説動画の時期から問題変わっててフラグの対応不要になってたわ
// 一応、解説動画だと"#0- +"の順番でしたね
// あと問題文にピリオドのプラグあるけど、そんなのなくね？
//
// ft_substr_to_num関数、よくできてんな。。。普通にすごすぎ
// 動画05の17:00くらいからのエラー処理も対策
// 20230318 動画05 6:00くらいから

// 解説の変換指定子はdiuxXefgcspn% かな？(文字が潰れている。。。)
//--------------------------------------

#include "ft_printf.h"
//include "libftprintf.a"

int		ft_isdigit(int c);	// ライブラリ使うとはいえプロトタイプ宣言は要るっぽい
void	ft_putnbr_fd(int n, int fd);

void	ft_print_percent(t_flag *info);
int		ft_non_specifier(const char **p, const char **format, t_flag *info);
int		ft_output(const char **p, const char **format, va_list *arg, t_flag *info);
int		ft_substr_to_num(const char **format, va_list *arg, int mode, t_flag *info);
int		ft_strchr_order(const char *s, int c);
void	ft_init_flag(t_flag *s, int i);
void	ft_proc_per(const char **p, const char **format, int *i, va_list *arg);
void	ft_print_str(const char **p, const char **format, int *i);
int		ft_printf(const char *format, ...);

// di uxX efg c s p n %
// c s p di uxX %"
int	ft_output(const char **p, const char **format, va_list *arg, t_flag *info)
{
	if (info->specifier == -1)
		return (ft_non_specifier(p, format, info));
	(*format)++;
	// 変換指定子はcspdiuxX%が左から数字で格納されている
	// 変換指定子がc(char)かs(string)の場合
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
	// putlenは吐き出した文字数。fieldは全体の長さでなく空白部分の長さ
	return (info->putlen + info->field);


}


void	ft_proc_per(const char **p, const char **format, int *i, va_list *arg)
{
	int		num;
	t_flag	info;

	(*format)++;
	ft_init_flag(&info, *i);
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
