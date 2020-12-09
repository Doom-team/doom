/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:46:33 by clala             #+#    #+#             */
/*   Updated: 2020/02/20 19:01:48 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	int		is_spec_val(char *s, int flag)
{
	if (!*s)
		return (0);
	if (flag == ('n' | 'i') && (ft_strstr(s, "inf") ||
	ft_strstr(s, "nan")))
		return (1);
	else if (flag == 'i' && ft_strstr(s, "inf"))
		return (1);
	else if (flag == 'n' && ft_strstr(s, "nan"))
		return (1);
	return (0);
}

static void		f_exceptions(char *s)
{
	g_v.g_sign = g_v.space_sign ? ' ' : g_v.g_sign;
	g_v.g_sign = g_v.plus_sign ? '+' : g_v.g_sign;
	g_v.g_sign = s[0] == '-' ? '-' : g_v.g_sign;
	g_v.g_sign = is_spec_val(s, 'n') ? 0 : g_v.g_sign;
	g_v.g_sign_len = g_v.g_sign ? 1 : 0;
	g_v.width_sign = g_v.zero_sign ? '0' : ' ';
	g_v.width_sign = is_spec_val(s, 'n' | 'i') ? ' ' : g_v.width_sign;
	g_v.precis = is_spec_val(s, 'n' | 'i') ? 0 : g_v.precis;
}

static void		print_left_adjusted(char *s, int len)
{
	g_v.g_sign && !is_spec_val(s, 'n') ? t_buf_write(g_buf, &g_v.g_sign, 1) : 1;
	t_buf_write(g_buf, s, len);
	if (g_v.sharp_sign && !ft_strchr(s, '.') && !is_spec_val(s, 'n' | 'i'))
	{
		t_buf_write(g_buf, ".", 1);
		g_v.width--;
	}
	while (g_v.width > len + g_v.g_sign_len)
	{
		t_buf_write(g_buf, " ", 1);
		g_v.width--;
	}
}

static void		print_right_adjusted(char *s, int len)
{
	int			sign_printed;

	sign_printed = 0;
	if (g_v.g_sign && g_v.width_sign != ' ' && !is_spec_val(s, 'n'))
	{
		t_buf_write(g_buf, &g_v.g_sign, 1);
		sign_printed = 1;
	}
	while (g_v.precis < g_v.width && g_v.width > len + g_v.g_sign_len)
	{
		t_buf_write(g_buf, &g_v.width_sign, 1);
		g_v.width--;
	}
	if (g_v.g_sign && !sign_printed && !is_spec_val(s, 'n'))
	{
		t_buf_write(g_buf, &g_v.g_sign, 1);
	}
	t_buf_write(g_buf, s, ft_strlen(s));
	if (g_v.sharp_sign && !ft_strchr(s, '.') && !is_spec_val(s, 'n' | 'i'))
	{
		t_buf_write(g_buf, ".", 1);
		g_v.width--;
	}
}

void			printf_f(va_list *ap)
{
	char		*s;
	double		double_value;
	long double long_double_value;
	char		*tmp;

	g_v.size_spec = g_v.size_spec && g_v.size_spec != 'L' ? 0 : g_v.size_spec;
	if (g_v.size_spec == 'L')
	{
		long_double_value = va_arg(*ap, long double);
		s = ft_ldtoa(long_double_value, g_v.precis);
	}
	else
	{
		double_value = va_arg(*ap, double);
		s = ft_dtoa(double_value, g_v.precis);
	}
	f_exceptions(s);
	tmp = s;
	s = g_v.g_sign == '-' ? s + 1 : s;
	if (s && s[0])
		(g_v.minus_flag ? print_left_adjusted(s, ft_strlen(s)) :
		print_right_adjusted(s, ft_strlen(s)));
	free(tmp);
}
