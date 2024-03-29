/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_ull.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akisuzuk <akisuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 09:37:03 by akisuzuk          #+#    #+#             */
/*   Updated: 2023/03/27 21:44:45 by akisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	output(int i, char *base, unsigned long long *nummem)
{
	while (i > 0)
	{
		write(1, &base[nummem[i - 1]], 1);
		i--;
	}
}

void	ft_putnbr_base_ull(unsigned long long nbr, char *base)
{
	unsigned long long	basenum;
	unsigned long long	nummem[30];
	int					i;

	if (nbr == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
	}
	basenum = 0;
	while (base[basenum] != '\0')
		basenum++;
	i = 0;
	while (nbr > 0)
	{
		nummem[i] = nbr % basenum;
		nbr /= basenum;
		i++;
	}
	output(i, base, nummem);
}

/*
int	main(void)
{
	ft_putnbr_base(1260, "0123456789ABCDEF");
	printf("\n");
	ft_putnbr_base(123, "ab");
	printf("\n");
	ft_putnbr_base(-2147483648, "abcdefgh");
	ft_putnbr_base(0, "0123456789");
	ft_putchar('\n');
	ft_putnbr_base(1234, "0123456789");
	ft_putchar('\n');
	ft_putnbr_base(-1234, "0123456789");
	ft_putchar('\n');
	ft_putnbr_base(2147483647, "0123456789");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "0123456789");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "asf");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "asfa");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "a");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "+8we2");
	ft_putchar('\n');
	ft_putnbr_base(-2147483648, "-8we2");
	return (0);
}
*/
