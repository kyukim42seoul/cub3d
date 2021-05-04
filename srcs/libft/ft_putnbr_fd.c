/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:16:36 by baramjigi2        #+#    #+#             */
/*   Updated: 2020/11/23 01:41:03 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		temp;

	temp = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			temp = 1;
			n += 1;
		}
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd((n / 10), fd);
		c = n % 10 + 48 + temp;
		write(fd, &c, 1);
	}
	else
	{
		c = n + 48;
		write(fd, &c, 1);
	}
}
