/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:34:51 by baramjigi2        #+#    #+#             */
/*   Updated: 2020/11/26 13:43:10 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_char(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	index;
	unsigned int	len;
	unsigned int	start;
	unsigned int	end;
	char			*s2;

	if (!s1)
		return (NULL);
	index = 0;
	len = ft_strlen(s1);
	if (!*s1)
		return (s2 = (char *)malloc(0));
	while (check_char(s1[index], set))
		index++;
	start = index;
	index = len - 1;
	while (check_char(s1[index], set) && start < index)
		index--;
	end = index;
	s2 = ft_substr(s1, start, (size_t)(end - start + 1));
	if (!s2)
		return (0);
	return (s2);
}
