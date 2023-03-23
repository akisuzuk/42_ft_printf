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

#include "ft_printf.h"

static	void	ft_print_str(const char **p, const char **fmt, int *i)
{
	while (**fmt != '%' && **fmt)
		(*fmt)++;
	write(1, *p, *fmt - *p);
	*i += *fmt - *p;
}

int	ft_printf(const char *fmt, ...)
{
	va_list		arg;
	const char	*p;
	int			i;

	va_start(arg, fmt);
	i = 0;
	if (fmt == NULL)
		i = -1;
	while (i >= 0 && *fmt)
	{
		p = fmt;
		if (*p != '%')
			ft_print_str(&p, &fmt, &i);
		else
			ft_proc_per(&p, &fmt, &i, &arg);
		fmt++;
	}
	va_end (arg);
	return (i);
}
