/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:21:03 by kyukim            #+#    #+#             */
/*   Updated: 2020/11/23 01:39:39 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;

	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	while (n-- && (*p_s1 || *p_s2))
	{
		if (*p_s1 > *p_s2)
			return (1);
		else if (*p_s1 < *p_s2)
			return (-1);
		p_s1++;
		p_s2++;
	}
	return (0);
}
