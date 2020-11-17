/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:58:22 by grinko            #+#    #+#             */
/*   Updated: 2020/11/04 11:39:15 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_count_words(char const *s, char c)
{
	size_t words;

	words = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == 0))
			words++;
		s++;
	}
	return (words);
}

static size_t		ft_wordlen(char const *s, char c)
{
	size_t		i;

	i = 0;
	while ((*s != c) && *s)
	{
		i++;
		s++;
	}
	return (i);
}

static void			ft_delete(char ***res, size_t j)
{
	while (--j > 0)
		ft_strdel(&(*res)[j]);
	free(*res);
	*res = NULL;
}

static char			**ft_alloc_and_fill(char const *s, char c, char **res)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!(res[j] = ft_strsub(s, i, ft_wordlen(s + i, c))))
			{
				ft_delete(&res, j);
				return (NULL);
			}
			j++;
			i += ft_wordlen(s + i, c);
			continue ;
		}
		i++;
	}
	res[j] = NULL;
	return (res);
}

char				**ft_strsplit(char const *s, char c)
{
	char		**res;
	size_t		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	if ((res = (char **)malloc(sizeof(char *) * (words + 1))) == NULL)
		return (NULL);
	return (ft_alloc_and_fill(s, c, res));
}
