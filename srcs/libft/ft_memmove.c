/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:18:55 by kyukim            #+#    #+#             */
/*   Updated: 2020/11/23 01:39:01 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst < src)
	{
		while (len--)
			*p_dst++ = *p_src++;
	}
	else
	{
		p_src = p_src + len - 1;
		p_dst = p_dst + len - 1;
		while (len--)
			*p_dst-- = *p_src--;
	}
	return (dst);
}
