/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:13:06 by kyukim            #+#    #+#             */
/*   Updated: 2020/11/23 01:38:50 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	temp;
	unsigned char	*p_dst;
	unsigned char	*p_src;

	temp = (unsigned char)c;
	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	while (n--)
	{
		if (*p_src == temp)
		{
			*p_dst = *p_src;
			return (++p_dst);
		}
		*(p_dst++) = *(p_src++);
	}
	return (NULL);
}
