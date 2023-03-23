/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 17:53:37 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/22 17:53:37 by akisuzuk         ###   ########.fr       */
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

static	void	ft_print_str(const char **p, const char **format, int *i)
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

//int main(int argc, char const * argv[])
//{
//	ft_printf("xxx%dyyy%c", 3, "def");
//	//printf("c1=%c, c2=%c, i1=%d, i2=%d\n", 'a', 'z', 1, 9);
//	//ft_printf("c1=%c, c2=%c, i1=%d, i2=%d\n", 'a', 'z', 1, 9);
//	return 0;
//}
//
//
//
//	//p = (char *)var_arg(arg, char *);
//	//d = (int)var_arg(arg, int);
//	//c = (char)var_arg(arg, int);	// 読み込みは4バイトずつなのでcharを引っ張ってくる時もargの引数はintでずらした箇所を参照する
//
