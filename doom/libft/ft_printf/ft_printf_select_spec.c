/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_select_spec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:48:10 by clala             #+#    #+#             */
/*   Updated: 2020/02/20 19:03:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			select_size_spec(const char *format, int *i)
{
	int		j;
	int		len_size_spec;

	len_size_spec = 0;
	j = *i + g_v.len_format + 1;
	if (format[j] == 'l')
		g_v.size_spec = format[j + 1] == 'l' ? 'l' * 2 : 'l';
	else if (format[j] == 'h')
		g_v.size_spec = format[j + 1] == 'h' ? 'h' * 2 : 'h';
	else if (format[j] == 'L')
		g_v.size_spec = 'L';
	if (g_v.size_spec)
	{
		if (g_v.size_spec == 'h' || g_v.size_spec == 'l' ||
				g_v.size_spec == 'L')
			len_size_spec = 1;
		else
			len_size_spec = 2;
	}
	return (len_size_spec);
}

int			select_type_spec(const char *format, int *i)
{
	char	c;
	int		len_type_spec;

	len_type_spec = 0;
	c = format[*i + g_v.len_format + 1];
	if (c && ft_strchr("cspdiouxXbrf", c))
	{
		g_v.type_spec = c;
		len_type_spec = 1;
	}
	return (len_type_spec);
}

int			f_set_globals_default(void)
{
	g_v.plus_sign = 0;
	g_v.space_sign = 0;
	g_v.zero_sign = 0;
	g_v.sharp_sign = 0;
	g_v.width = 0;
	g_v.size_spec = 0;
	g_v.minus_flag = 0;
	g_v.params_changed = 0;
	g_v.precis = -1;
	g_v.len_format = 0;
	g_v.type_spec = 0;
	g_v.g_sign_len = 0;
	g_v.g_sign = 0;
	g_v.width_sign = 0;
	return (1);
}
