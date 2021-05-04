/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:19:28 by kyukim            #+#    #+#             */
/*   Updated: 2020/11/23 01:39:03 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	temp;
	unsigned char	*p_temp;

	temp = (unsigned char)c;
	p_temp = (unsigned char *)b;
	while (len--)
		*(p_temp++) = temp;
	return (b);
}
