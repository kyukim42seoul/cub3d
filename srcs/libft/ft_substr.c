/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:23:40 by baramjigi2        #+#    #+#             */
/*   Updated: 2020/11/23 01:39:49 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	char	*temp;

	s2 = (char *)malloc(sizeof(char) * (len + 1));
	temp = s2;
	if (!s)
		return (NULL);
	if (!s2)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		*temp = '\0';
		return (s2);
	}
	while (len-- != 0 && *s)
		*temp++ = *(s + start++);
	*temp = '\0';
	return (s2);
}
