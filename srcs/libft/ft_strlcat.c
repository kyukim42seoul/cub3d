/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:20:06 by kyukim            #+#    #+#             */
/*   Updated: 2020/11/23 01:39:28 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = 0;
	if (dstsize >= (ft_strlen(dst) + 1))
	{
		len = ft_strlen(dst) + ft_strlen(src);
		while (dstsize-- && *dst)
			dst++;
		while (dstsize-- && *src)
			*dst++ = *src++;
		*dst = '\0';
		return (len);
	}
	else
		len = (size_t)ft_strlen(src) + dstsize;
	return (len);
}
