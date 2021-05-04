/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:24:02 by kyukim            #+#    #+#             */
/*   Updated: 2020/11/23 01:39:44 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		cc;
	const char	*temp;

	cc = (char)c;
	temp = s;
	while (*s)
		s++;
	if (*s == '\0' && cc == '\0')
		return ((char *)s);
	s--;
	while (*s && s > temp)
	{
		if (*s == cc)
			return ((char *)s);
		s--;
	}
	if (*s == cc)
		return ((char *)s);
	return (NULL);
}
