/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:20:31 by kyukim            #+#    #+#             */
/*   Updated: 2020/11/23 01:39:30 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	size;

	if (!dst)
		return (0);
	size = ft_strlen(src);
	if (dstsize == 0)
		return (size);
	else if (dstsize > 1)
	{
		while (--dstsize && *src)
			*dst++ = *src++;
	}
	*dst = '\0';
	return (size);
}
