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

int	ft_printf(const char *format, ...);

int	ft_printf(const char *format, ...)
{
	va_list	arg;	// argがこれ以降のva_startとかva_listの第一引数になる
	va_start(arg, format); // 第二引数には、プロトタイプ宣言の第一引数を設定
	const char	*p;
	int			i;

	p = format;
	// 第一引数を読み込んで出力の枠を確定
	while (p[i] != '\0')
	{
		if (p[i] == '%')
		{
		}
	}

	// 第二引数以降を拾っていって格納してまとめて表示

	


	va_end (arg); // va_startとセット。可変長引数の処理を完了
}


int main(int argc, char const *argv[])
{
	write(1, "hello!\n", 7);
	printf("c1=%c, c2=%c, i1=%d, i2=%d\n", 'a', 'z', 1, 9);
	//ft_printf("c1=%c, c2=%c, i1=%d, i2=%d\n", 'a', 'z', 1, 9);
	return 0;
}
