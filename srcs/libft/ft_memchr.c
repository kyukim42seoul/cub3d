/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:16:42 by kyukim            #+#    #+#             */
/*   Updated: 2020/11/23 01:38:53 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char temp;
	unsigned char *ps;

	temp = (unsigned char)c;
	ps = (unsigned char *)s;
	while (n--)
	{
		if (*ps == temp)
			return (ps);
		ps++;
	}
	return (NULL);
}
