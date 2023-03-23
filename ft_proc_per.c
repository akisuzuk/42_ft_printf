/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proc_per.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:30:32 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/23 18:14:41 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_substr_to_num(const char **fmt, va_list *arg,
							int mode, t_flag *info)
{
	int		num;

	num = -1;
	if (**fmt == '*')
	{
		num = va_arg(*arg, int);
		if (num < 0 && !mode)
		{
			num *= -1;
			info -> flag[0] = 1;
		}
		else if (num < 0)
			num = -1;
		(*fmt)++;
	}
	else if (mode || ft_isdigit(**fmt))
	{
		num = 0;
		while (ft_isdigit(**fmt))
			num = num * 10 + (*((*fmt)++) - '0');
	}
	return (num);
}

int	ft_strchr_order(const char *s, int c)
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
	return (-1);
}

void	ft_init_flag(t_flag *s)
{
	s->flag[0] = 0;
	s->flag[1] = 0;
	s->field = -1;
	s->acc = -1;
	s->specifier = -1;
	s->putlen = 0;
}

void	ft_proc_per(const char **p, const char **fmt, int *i, va_list *arg)
{
	int		num;
	t_flag	info;

	ft_init_flag(&info);
	(*fmt)++;
	num = ft_strchr_order("-0", **fmt);
	while (num >= 0)
	{
		info.flag[num] = 1;
		(*fmt)++;
	}
	info.field = ft_substr_to_num(fmt, arg, 0, &info);
	if (**fmt == '.')
	{
		(*fmt)++;
		info.acc = ft_substr_to_num(fmt, arg, 1, &info);
	}
	info.specifier = ft_strchr_order("cspdiuxX%", **fmt);
	num = ft_output(p, fmt, arg, &info);
	*i += num;
}
