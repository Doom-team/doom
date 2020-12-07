/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:43:18 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:56:46 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words(char const *s, char c)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			return (counter);
		counter++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (counter);
}

static void	free_arr(char ***arr)
{
	int		i;

	i = 0;
	while (*arr[i])
		free(*arr[i++]);
	free(*arr);
	arr = NULL;
}

static char	*word_to_array(int start, int end, char *s, char *arrs)
{
	int		j;

	if (!(arrs = (char *)ft_strnew(end - start + 1)))
		return (NULL);
	j = 0;
	while (start < end)
		arrs[j++] = s[start++];
	arrs[j] = '\0';
	return (arrs);
}

static int	copy_words(char *s, char c, char **arr)
{
	int		i;
	int		start;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && (char)s[i] == c)
			i++;
		start = i;
		if (!s[i])
			break ;
		while (s[i] && (char)s[i] != c)
			i++;
		if (!(arr[count] = word_to_array(start, i, (char *)s, arr[count])))
		{
			free_arr(&arr);
			return (0);
		}
		++count;
	}
	arr[count] = 0;
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**arr;

	if (!s || !c || !(arr = (char **)malloc(sizeof(char *) *
		(words(s, c) + 1))))
		return (NULL);
	if (!copy_words((char *)s, c, arr))
		return (NULL);
	return (arr);
}
