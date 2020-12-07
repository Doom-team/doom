/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintprepr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:24:59 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		normalize_integers(char **arg1, char **arg2)
{
	size_t		len_arg1;
	size_t		len_arg2;

	len_arg1 = ft_strlen(*arg1);
	len_arg2 = ft_strlen(*arg2);
	if (len_arg1 > len_arg2)
		(*arg2) = ft_strjoinfree(ft_strnewchr(len_arg1 - len_arg2, '0'),
				*arg2, 1, 1);
	else if (len_arg1 < len_arg2)
		(*arg1) = ft_strjoinfree(ft_strnewchr(len_arg2 - len_arg1, '0'),
				*arg1, 1, 1);
}

static void		normalize_decimals(char **arg1, char **arg2)
{
	char		*decpt_1;
	char		*decpt_2;
	intmax_t	decimals_1;
	intmax_t	decimals_2;

	decpt_1 = ft_strchr(*arg1, '.');
	decpt_2 = ft_strchr(*arg2, '.');
	decimals_1 = (decpt_1) ? ft_strlen(*arg1) - 1 - (decpt_1 - (*arg1)) : 0;
	decimals_2 = (decpt_2) ? ft_strlen(*arg2) - 1 - (decpt_2 - (*arg2)) : 0;
	if (decpt_1 && !decpt_2)
		(*arg2) = ft_strjoinfree(*arg2, ft_strjoinfree(".",
				ft_strnewchr(decimals_1, '0'), 0, 1), 1, 1);
	else if (!decpt_1 && decpt_2)
		(*arg1) = ft_strjoinfree(*arg1, ft_strjoinfree(".",
				ft_strnewchr(decimals_2, '0'), 0, 1), 1, 1);
	else if (decpt_1 && decpt_2)
	{
		if (decimals_1 > decimals_2)
			(*arg2) = ft_strjoinfree(
				*arg2, ft_strnewchr(decimals_1 - decimals_2, '0'), 1, 1);
		if (decimals_1 < decimals_2)
			(*arg1) = ft_strjoinfree(
				*arg1, ft_strnewchr(decimals_2 - decimals_1, '0'), 1, 1);
	}
}

void			ft_bintprepr(char **arg1, char **arg2)
{
	char		*dup_arg1;
	char		*dup_arg2;
	int8_t		sign_1;
	int8_t		sign_2;

	sign_1 = ((*arg1)[0] == '-');
	sign_2 = ((*arg2)[0] == '-');
	dup_arg1 = ft_strdup((*arg1) + sign_1);
	dup_arg2 = ft_strdup((*arg2) + sign_2);
	ft_free("2", *arg1, *arg2);
	normalize_decimals(&dup_arg1, &dup_arg2);
	normalize_integers(&dup_arg1, &dup_arg2);
	(*arg1) = (sign_1) ? ft_strjoinfree("-", dup_arg1, 0, 1) : dup_arg1;
	(*arg2) = (sign_2) ? ft_strjoinfree("-", dup_arg2, 0, 1) : dup_arg2;
}
