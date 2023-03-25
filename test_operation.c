/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:59:23 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/25 19:16:52 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

// 変換指定子比較
// di uxX efg c s p n %
// c s p di uxX %"

// フラグ比較
// "#0- +""
// "-0"

// ヘッダーにかくプロトタイプは、要は.cファイルの中で完結しないやつだけ

//int main(int argc, char const * argv[])
int	main(void)
{
	int num;

	//num = ft_printf("char[%c] string [%s] pointer[%p] int[%d] int[%i]\n", 'a', "abc", "ptr", -123, -456);
	//num = ft_printf("decimal[%u] hexa [%x] HEXA[%X] percent[%%]\n", 31, 31, 31);
	//write(1, "\n", 1);

	// 幅指定なしの場合は実装できてそう(改定後の今の課題なら必須パートはクリアか)

	// テストケースとの整合チェック
	//printf("-----s chack-----\n");
	//printf(" NULL [%s] NULL \n", NULL);
	//ft_printf(" NULL [%s] NULL \n", NULL);

	//printf("-----s chack-----\n");
	//printf(" NULL [%s] NULL \n", NULL);
	//ft_printf(" NULL [%s] NULL \n", NULL);

	printf("-----p chack-----\n");
	//int *p;
	int origin;
	int myfunc;

	//*p = 42;
	origin = printf("%d\n", 0);
	myfunc = ft_printf("%d\n", 0);
	printf("origin ret = %d\n", origin);
	printf("myfunc ret = %d\n", myfunc);

	// 幅指定ありの場合が怪しいのでチェック...
	//num = ft_printf("xxx[%4.3d]yyy[%s]\n", 5, "def");
	//num = ft_printf("xxx[%4.3d]yyy[%s]\n", 12345, "def");



	//write(1, "\n", 1);
	//write(1, "num=", 4);
	//ft_putnbr_fd(num, 1);

	//printf("c1=%c, c2=%c, i1=%d, i2=%d\n", 'a', 'z', 1, 9);
	//ft_printf("c1=%c, c2=%c, i1=%d, i2=%d\n", 'a', 'z', 1, 9);
	return 0;
}



//	//p = (char *)var_arg(arg, char *);
//	//d = (int)var_arg(arg, int);
//	//c = (char)var_arg(arg, int);
// 読み込みは4バイトずつなのでcharを引っ張ってくる時もargの引数はintでずらした箇所を参照する

