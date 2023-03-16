/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:35:53 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/16 23:46:46 by akisuzuk         ###   ########.fr       */
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
	int	flag[3]; // ボーナスありなら5
	int	field;
	int	acc;
	//int	modifier;  // ボーナスありなら長さ修飾子も解放
	int	specifier;
	int	putnum;
	int	putlen;
	int	copy_acc;
}					t_flag;

#endif //__INCLUDE_LIBFT_H__
