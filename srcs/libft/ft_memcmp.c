/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:17:21 by kyukim            #+#    #+#             */
/*   Updated: 2020/11/23 01:38:55 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ps1;
	unsigned char	*ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	while (n--)
	{
		if (*ps1 > *ps2)
			return (*ps1 - *ps2);
		else if (*ps1 < *ps2)
			return (*ps1 - *ps2);
		else
		{
			ps1++;
			ps2++;
		}
	}
	return (0);
}
