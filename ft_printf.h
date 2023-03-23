/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:35:53 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/23 15:32:55 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
//# include <climits>
# include <limits.h>
# include <stdbool.h>
# include <stdarg.h>

typedef struct s_flag
{
	int	flag[2];
	int	field;
	int	acc;
	int	specifier;
	int	putlen;
}					t_flag;

size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
void	ft_putnbr_fd(int n, int fd);

void	ft_putnbr_base(int nbr, char *base);

void	ft_print_percent(t_flag *info);
void	ft_unsigned_print(va_list *arg, t_flag *info);
void	ft_int_print(va_list *arg, t_flag *info);

void	ft_putchar_rep(char c, int fd, int rep);
int		ft_get_digit(int num, int base);
void	ft_get_putlen(t_flag *info, int num);

int		ft_output(const char **p, const char **fmt, va_list *arg, t_flag *info);
void	ft_proc_per(const char **p, const char **fmt, int *i, va_list *arg);
int		ft_printf(const char *fmt, ...);

#endif //__INCLUDE_LIBFT_H__
