/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_per_ele.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:30:32 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/21 20:32:56 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
