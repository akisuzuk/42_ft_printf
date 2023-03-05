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
//--------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//include "libftprintf.a"
#include <stdarg.h>

void	ft_print_str(const char **p, const char **format, int *i);
int		ft_printf(const char *format, ...);

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
	const char	*p;
	int			i;
	va_list		arg;	// argがこれ以降のva_startとかva_listの第一引数になる

	i = 0;
	va_start(arg, format); // 第二引数には、プロトタイプ宣言の第一引数を設定
	if (format == NULL)
		i = -1;
	i = 0;
	while (i >= 0 && *format)
	{
		p = format;
		if (*p != '%')
			ft_print_str(&p, &format, &i);
		else
			return (0);
			//ft_proc_per(*p, *format, &i, &arg)
	}

	// 第二引数以降を拾っていって格納してまとめて表示

	va_end (arg); // va_startとセット。可変長引数の処理を完了
	return (i);
}

int main(int argc, char const * argv[])
{
	write(1, "hello!\n", 7);
	printf("c1=%c, c2=%c, i1=%d, i2=%d\n", 'a', 'z', 1, 9);
	//ft_printf("c1=%c, c2=%c, i1=%d, i2=%d\n", 'a', 'z', 1, 9);
	return 0;
}



	//p = (char *)var_arg(arg, char *);
	//d = (int)var_arg(arg, int);
	//c = (char)var_arg(arg, int);	// 読み込みは4バイトずつなのでcharを引っ張ってくる時もargの引数はintでずらした箇所を参照する
