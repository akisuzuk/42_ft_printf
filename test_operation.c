/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:59:23 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/27 21:25:49 by akisuzuk         ###   ########.fr       */
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
	int num1;
	int num2;

	// 幅指定なしの場合は実装できてそう(改定後の今の課題なら必須パートはクリアか)


	printf("-----p chack-----\n");
	//int *p;
	int origin;
	int myfunc;

	//*p = 42;
	origin = printf("%p\n", (void *)-15);
	myfunc = ft_printf("%p\n", (void *)-15);
	printf("origin ret = %d\n", origin);
	printf("myfunc ret = %d\n", myfunc);

	// 幅指定ありの場合が怪しいのでチェック...
	/*
	printf("\n-----field acc check-----\n");
	num1 = printf("[%10.5s]\n", "abcde");
	num2 = ft_printf("[%10.5s]\n", "abcde");
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	*/
	return 0;
}



//	//p = (char *)var_arg(arg, char *);
//	//d = (int)var_arg(arg, int);
//	//c = (char)var_arg(arg, int);
// 読み込みは4バイトずつなのでcharを引っ張ってくる時もargの引数はintでずらした箇所を参照する

