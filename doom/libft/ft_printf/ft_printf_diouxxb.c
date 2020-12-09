/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diouxxb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:46:29 by clala             #+#    #+#             */
/*   Updated: 2020/02/20 18:59:05 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		get_base(void)
{
	if (g_v.type_spec == 'o')
		return (8);
	else if (g_v.type_spec == 'x' || g_v.type_spec == 'X')
		return (16);
	else if (g_v.type_spec == 'b')
		return (2);
	else
		return (10);
}

static char		*get_diouxxb_string(t_data value)
{
	char		*s;

	if (!(s = NULL) && (g_v.type_spec == 'd' || g_v.type_spec == 'i'))
	{
		if (!g_v.size_spec)
			s = ft_itoa_base(value.int_, get_base());
		else if (g_v.size_spec == 'l' || g_v.size_spec == 'l' * 2)
			s = ft_ltoa_base(value.long_, get_base());
		else if (g_v.size_spec == 'h')
			s = ft_itoa_base(value.short_, get_base());
		else if (g_v.size_spec == 'h' * 2)
			s = ft_itoa_base(value.char_, get_base());
	}
	else
	{
		if (!g_v.size_spec)
			s = ft_uitoa_base(value.uint_, get_base());
		else if (g_v.size_spec == 'l' || g_v.size_spec == 'l' * 2)
			s = ft_ultoa_base(value.ulong_, get_base());
		else if (g_v.size_spec == 'h')
			s = ft_uitoa_base(value.ushort_, get_base());
		else if (g_v.size_spec == 'h' * 2)
			s = ft_uitoa_base(value.uchar_, get_base());
	}
	return (s);
}

void			printf_diouxxb(va_list *ap)
{
	char		*s;
	t_data		value;

	value.intmax_ = va_arg(*ap, intmax_t);
	g_v.size_spec = g_v.size_spec == 'L' ? 0 : g_v.size_spec;
	s = get_diouxxb_string(value);
	s = (g_v.type_spec == 'X' ? ft_strupr(s) : ft_strlwr(s));
	diouxxb_printer(s);
	free(s);
}
