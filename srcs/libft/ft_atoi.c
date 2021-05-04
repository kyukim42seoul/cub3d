/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:24:28 by baramjigi2        #+#    #+#             */
/*   Updated: 2020/11/26 13:44:40 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_space(const char *str)
{
	if (*str == '\t' || *str == '\n' || *str == '\v')
		return (1);
	else if (*str == '\f' || *str == '\r' || *str == ' ')
		return (1);
	else
		return (0);
}

static int		check_sign(const char *str)
{
	if (*str == '-' || *str == '+')
	{
		str++;
		if (*str == '-' || *str == '+')
			return (0);
		str--;
	}
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	while (check_space(str))
		str++;
	if (check_sign(str))
	{
		sign *= check_sign(str);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return (sign * nbr);
}
