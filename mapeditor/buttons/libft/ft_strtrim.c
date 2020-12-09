/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:59:03 by grinko            #+#    #+#             */
/*   Updated: 2019/09/12 11:59:45 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	bl(char c)
{
	return (c == ' ' || c == ',' || c == '\t' || c == '\n');
}

char		*ft_strtrim(char const *s)
{
	int		len;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s) - 1;
	while (bl((char)s[i]))
		i++;
	while (bl((char)s[len]) && len > i)
		len--;
	if (len < i)
		return (ft_strdup(""));
	return (ft_strsub(s, i, len - i + 1));
}
