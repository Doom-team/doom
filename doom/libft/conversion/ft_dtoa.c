/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:28:14 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 23:45:15 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#define DOUBLE_EXPONENT_WIDTH 11
#define MANT_WID 52
#define DOUBLE_SIZE 64

char			*double_is_exception(double n, t_double t_dbl)
{
	char		*str;
	uintmax_t	double_implicit_mantissa_bit;
	int			double_bias;
	int			double_exponent_max;

	double_implicit_mantissa_bit = 1L << MANT_WID;
	double_bias = ((1 << (DOUBLE_EXPONENT_WIDTH - 1)) - 1);
	double_exponent_max = 2048 - 1 - double_bias - MANT_WID;
	str = NULL;
	if (t_dbl.mantissa == 0 && t_dbl.exponent == 0)
		str = ft_strdup("0");
	else if (n != n)
		str = ft_strdup("nan");
	else if (t_dbl.exponent == double_exponent_max &&
	t_dbl.mantissa == double_implicit_mantissa_bit)
	{
		if (t_dbl.sign)
			str = ft_strdup("-inf");
		else
			str = ft_strdup("inf");
	}
	return (str);
}

char			*ft_dtoa(double n, int precision)
{
	t_double	num;
	char		*str;

	num.sign = *(uintmax_t *)&n >> (DOUBLE_SIZE - 1);
	num.exponent = (short)((*(uintmax_t *)&n << 1 >> (MANT_WID
			+ 1)) - ((1 << (DOUBLE_EXPONENT_WIDTH - 1)) - 1) - MANT_WID);
	num.mantissa = ((*(uintmax_t *)&n & 4503599627370495U) | (1L << MANT_WID));
	str = NULL;
	if ((str = double_is_exception(n, num)))
		return (str);
	else
	{
		str = ft_utoa_base(num.mantissa, 0);
		if (num.exponent > 0)
			while (num.exponent-- > 0)
				str = ft_bintmltpl(str, 2);
		else
			while (num.exponent++ < 0)
				str = ft_bintdivsn(str, 2);
	}
	str = ft_bintroundfree(str, ((precision >= 0) ? precision : 6), 1);
	return ((num.sign) ? ft_strjoinfree("-", str, 0, 1) : str);
}
