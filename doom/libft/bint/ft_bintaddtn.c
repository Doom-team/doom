/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintaddtn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:23:41 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_bintaddition(char *arg1, char *arg2)
{
	char	*str;
	int32_t	carry;
	int32_t	sum;
	int32_t	i;

	str = ft_strdup(arg1);
	i = ft_strlen(str) - 1;
	carry = 0;
	while (i >= 0)
	{
		if (str[i] == '.')
			i--;
		sum = carry + ft_ctoi(arg1[i]) + ft_ctoi(arg2[i]);
		str[i--] = ft_itoc(sum % 10);
		carry = sum > 9;
	}
	if (carry)
		str = ft_strjoinfree("1", str, 0, 1);
	str = ft_bintfmt(str);
	return (str);
}

static char	*sign_handler(char operation, char **arg1, char **arg2)
{
	char	*str;
	int8_t	sign;

	ft_bintprepr(arg1, arg2);
	if ((*arg2)[0] == '-')
		operation = (operation == '+') ? '-' : '+';
	sign = (operation == '+') ? 1 : -1;
	ft_strswap(arg1, arg2);
	if ((*arg2)[0] == '-')
		operation = (operation == '+') ? '-' : '+';
	(*arg1) = ft_strtrimstart((*arg1), "-");
	(*arg2) = ft_strtrimstart((*arg2), "-");
	if (operation == '-' && ft_bintcmp(*arg1, *arg2) < 0)
	{
		sign = -sign;
		ft_strswap(arg1, arg2);
	}
	str = (operation == '+') ? ft_bintaddition(*arg1, *arg2) :
		ft_bintsubtrn(*arg1, *arg2);
	if (sign == -1 && ft_strcmp(str, "0") != 0)
		str = ft_strjoinfree("-", str, 0, 1);
	return (str);
}

char		*ft_bintaddtn(char *arg1, char *arg2)
{
	char	*arg1_dup;
	char	*arg2_dup;
	char	*str;

	arg1_dup = ft_strdup(arg1);
	arg2_dup = ft_strdup(arg2);
	if (!arg1_dup || !arg2_dup)
		return (NULL);
	str = sign_handler('+', &arg1_dup, &arg2_dup);
	ft_free("4", arg1, arg2, arg1_dup, arg2_dup);
	return (str);
}
