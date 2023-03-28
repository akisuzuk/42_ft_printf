/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:59:23 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/28 21:31:10 by akisuzuk         ###   ########.fr       */
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

	// 幅指定ありの場合が怪しいのでチェック...

	printf("\n-----field acc check-----\n");


	num1 = printf("[%010.5s]\n", "abcde");
	num2 = ft_printf("[%010.5s]\n", "abcde");
	printf("---test 1-------------\n");
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);	
	printf("---test 2-------------\n");
	num1 = printf("[%-010.3s]\n", "abcde");
	num2 = ft_printf("[%-010.3s]\n", "abcde");
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 3-------------\n");
	num1 = printf("[%-10.3s]\n", "abcde");
	num2 = ft_printf("[%-10.3s]\n", "abcde");
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 4-------------\n");
	num1 = printf("[%10.3s]\n", "abcdefghijk");
	num2 = ft_printf("[%10.3s]\n", "abcdefghijk");
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 5-------------\n");
	num1 = printf("[%3s]\n", "abcde");
	num2 = ft_printf("[%3s]\n", "abcde");
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);

	printf("---test 6-------------\n");
	num1 = printf("[%10.3d]\n", -12345);
	num2 = ft_printf("[%10.3d]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 6.1-------------\n");
	num1 = printf("[%010d]\n", 12345);
	num2 = ft_printf("[%010d]\n", 12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 6.2-------------\n");
	num1 = printf("[%010.3d]\n", 12345);
	num2 = ft_printf("[%010.3d]\n", 12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 7-------------\n");
	num1 = printf("[%010.3d]\n", -12345);
	num2 = ft_printf("[%010.3d]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 8-------------\n");
	num1 = printf("[%-010.3d]\n", -12345);
	num2 = ft_printf("[%-010.3d]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	
	printf("---test 9-------------\n");
	num1 = printf("[%20.3p]\n", "42");
	num2 = ft_printf("[%20.3p]\n", "42");
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 10-------------\n");
	num1 = printf("[%020.3p]\n", "42");
	num2 = ft_printf("[%020.3p]\n", "42");
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 11-------------\n");
	num1 = printf("[%-020.3p]\n", "42");
	num2 = ft_printf("[%-020.3p]\n", "42");
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);	
	printf("---test 12-------------\n");
	num1 = printf("[%p]\n", "42");
	num2 = ft_printf("[%p]\n", "42");
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	
	printf("---test 13-------------\n");
	num1 = printf("[%10.3i]\n", -12345);
	num2 = ft_printf("[%10.3i]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 14-------------\n");
	num1 = printf("[%010.3i]\n", -12345);
	num2 = ft_printf("[%010.3i]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 15-------------\n");
	num1 = printf("[%-010.3i]\n", -12345);
	num2 = ft_printf("[%-010.3i]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	
	printf("---test 16-------------\n");
	num1 = printf("[%10.3u]\n", -12345);
	num2 = ft_printf("[%10.3u]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 16.1-------------\n");
	num1 = printf("[%010u]\n", 12345);
	num2 = ft_printf("[%010u]\n", 12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 16.2-------------\n");
	num1 = printf("[%010.3u]\n", 12345);
	num2 = ft_printf("[%010.3u]\n", 12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 17-------------\n");
	num1 = printf("[%010.3u]\n", -12345);
	num2 = ft_printf("[%010.3u]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 18-------------\n");
	num1 = printf("[%-010.3u]\n", -12345);
	num2 = ft_printf("[%-010.3u]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);

	printf("---test 19-------------\n");
	num1 = printf("[%10.3x]\n", -12345);
	num2 = ft_printf("[%10.3x]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 19.1-------------\n");
	num1 = printf("[%010x]\n", 12345);
	num2 = ft_printf("[%010x]\n", 12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 19.2-------------\n");
	num1 = printf("[%010.3x]\n", 12345);
	num2 = ft_printf("[%010.3x]\n", 12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 20-------------\n");
	num1 = printf("[%010.3x]\n", -12345);
	num2 = ft_printf("[%010.3x]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);
	printf("---test 21-------------\n");
	num1 = printf("[%-010.3x]\n", -12345);
	num2 = ft_printf("[%-010.3x]\n", -12345);
	printf("origin ret = %d\n", num1);
	printf("myfunc ret = %d\n", num2);

	return 0;
}



//	//p = (char *)var_arg(arg, char *);
//	//d = (int)var_arg(arg, int);
//	//c = (char)var_arg(arg, int);
// 読み込みは4バイトずつなのでcharを引っ張ってくる時もargの引数はintでずらした箇所を参照する

	// write(1, "acc=", 4);
	// ft_putnbr_fd(info->acc, 1);
	// write(1, "\n", 1);