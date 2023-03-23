/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:35:53 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/23 11:36:09 by akisuzuk         ###   ########.fr       */
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
	int	flag[2]; // ボーナスありなら5
	int	field;
	int	acc;
	//int	modifier;  // ボーナスありなら長さ修飾子も解放
	int	specifier;
	//int	putnum;
	int	putlen;
	//int	copy_acc;
}					t_flag;

size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);	// ライブラリ使うとはいえプロトタイプ宣言は要るっぽい
void	ft_putnbr_fd(int n, int fd);

void	ft_putnbr_base(int nbr, char *base);
int		ft_output(const char **p, const char **format, va_list *arg, t_flag *info);
void	ft_proc_per(const char **p, const char **format, int *i, va_list *arg);
int		ft_printf(const char *format, ...);

#endif //__INCLUDE_LIBFT_H__
