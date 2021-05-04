/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyukim <kyukim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:56:50 by baramjigi2        #+#    #+#             */
/*   Updated: 2020/11/26 13:51:16 by kyukim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_cnt(char const *s, char c)
{
	int		cnt;
	int		index;

	cnt = 0;
	index = 1;
	if (ft_strlen(s) == (unsigned long)index && s[index - 1 != c])
		cnt++;
	while (s[index])
	{
		if (s[index - 1] != c && s[index] == c)
			cnt++;
		else if (s[index] != c
		&& (unsigned long)index == (ft_strlen(s) - 1))
			cnt++;
		index++;
	}
	return (cnt);
}

static char		*cpy_arr(char const *s, char c, int index)
{
	int		start;

	if (!s)
	{
		return (NULL);
	}
	start = index;
	while (s[index] && s[index] != c)
	{
		if ((unsigned long)index == ft_strlen(s))
			return (ft_substr(s, start, (index - start)));
		index++;
	}
	return (ft_substr(s, start, (index - start)));
}

static int		check_output(char **output, int cnt)
{
	int		index;
	int		temp;

	index = 0;
	temp = cnt;
	while (temp)
	{
		if (!output[index])
		{
			index = 0;
			while (output[index] && index < cnt)
				free(output[index++]);
			free(output);
			return (0);
		}
		index++;
		temp--;
	}
	return (1);
}

static char		**null_pointer_to_pointer(void)
{
	char	**output;

	output = (char **)malloc(sizeof(char *) * 1);
	output[0] = NULL;
	return (output);
}

char			**ft_split(char const *s, char c)
{
	int		index;
	int		cnt;
	char	**output;

	if (!s)
		return (NULL);
	if (!*s)
		return (null_pointer_to_pointer());
	index = 1;
	if (!(output = (char **)malloc(sizeof(char *) * (check_cnt(s, c) + 1))))
		return (NULL);
	cnt = 0;
	if (s[index - 1] != c)
		output[cnt++] = cpy_arr(s, c, 0);
	while (s[index])
	{
		if (s[index - 1] == c && s[index] != c)
			output[cnt++] = cpy_arr(s, c, index);
		index++;
	}
	output[cnt] = NULL;
	if (check_output(output, check_cnt(s, c)))
		return (output);
	return (NULL);
}
