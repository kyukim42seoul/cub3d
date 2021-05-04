/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:07:50 by baramjigi2        #+#    #+#             */
/*   Updated: 2020/11/26 13:03:52 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*rev_arr(char *s)
{
	int		len;
	int		end;
	int		index;
	char	temp;

	len = ft_strlen(s);
	end = len - 1;
	index = 0;
	if (s[index] == '-')
		index++;
	len /= 2;
	while (len--)
	{
		temp = s[index];
		s[index] = s[end];
		s[end] = temp;
		index++;
		end--;
	}
	return (s);
}

static void		input_nbr(char *s, long long n)
{
	if (n >= 10)
	{
		*s = n % 10 + 48;
		input_nbr(++s, (n / 10));
	}
	else if (n < 10)
	{
		*s = n + 48;
		s++;
		*s = '\0';
	}
}

static int		check_cnt_zero(long long n)
{
	int		number_zero;

	number_zero = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		number_zero++;
		n /= 10;
	}
	return (number_zero);
}

char			*ft_itoa(int n)
{
	char		*output;
	long long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		if (!(output = (char *)malloc(sizeof(char) * check_cnt_zero(nbr) + 2)))
			return (NULL);
		nbr *= -1;
		*output = '-';
		input_nbr(++output, nbr);
		output--;
	}
	else
	{
		if (!(output = (char *)malloc(sizeof(char) * check_cnt_zero(nbr) + 1)))
			return (NULL);
		input_nbr(output, nbr);
	}
	return (rev_arr(output));
}
