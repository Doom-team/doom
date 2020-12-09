/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diouxxb_printer.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:45:48 by clala             #+#    #+#             */
/*   Updated: 2020/02/20 18:59:05 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	hex_bin_prefix_printer(char *s)
{
	if (g_v.sharp_sign && ft_strchr("bxX", g_v.type_spec)
			&& s[0] && s[0] != '0')
	{
		if (g_v.type_spec == 'b')
			t_buf_write(g_buf, "0b", 2);
		else
		{
			g_v.type_spec == 'x' ? t_buf_write(g_buf, "0x", 2) : 1;
			g_v.type_spec == 'X' ? t_buf_write(g_buf, "0X", 2) : 1;
		}
	}
}

static void	print_left_adjusted(char *s, int len)
{
	int		sign_printed;

	sign_printed = g_v.g_sign ? 1 : 0;
	sign_printed ? t_buf_write(g_buf, &g_v.g_sign, 1) : 1;
	g_v.width = g_v.g_sign ? g_v.width - 1 : g_v.width;
	hex_bin_prefix_printer(s);
	while (g_v.precis > len)
	{
		t_buf_write(g_buf, "0", 1);
		g_v.precis--;
		g_v.width--;
	}
	t_buf_write(g_buf, s, len);
	while (g_v.width > len)
	{
		g_v.width--;
		t_buf_write(g_buf, &g_v.width_sign, 1);
	}
}

static void	print_right_adjusted(char *s, int len)
{
	int		sign_printed;

	sign_printed = g_v.g_sign && (g_v.width <= len) ? 1 : 0;
	sign_printed ? t_buf_write(g_buf, &g_v.g_sign, 1) : 1;
	if (g_v.g_sign && !sign_printed && g_v.width_sign == '0')
	{
		t_buf_write(g_buf, &g_v.g_sign, 1);
		sign_printed = 1;
	}
	g_v.width = g_v.g_sign ? g_v.width - 1 : g_v.width;
	g_v.width_sign == '0' ? hex_bin_prefix_printer(s) : 1;
	while (g_v.width > ft_imaxval("2", g_v.precis, len))
	{
		t_buf_write(g_buf, &g_v.width_sign, 1);
		g_v.width--;
	}
	!sign_printed && g_v.g_sign ? t_buf_write(g_buf, &g_v.g_sign, 1) : 1;
	g_v.width_sign == ' ' ? hex_bin_prefix_printer(s) : 1;
	while (g_v.precis > len)
	{
		t_buf_write(g_buf, "0", 1);
		g_v.precis--;
	}
	t_buf_write(g_buf, s, len);
}

static void	f_exceptions(char *s)
{
	g_v.g_sign = g_v.space_sign ? ' ' : g_v.g_sign;
	g_v.g_sign = g_v.plus_sign ? '+' : g_v.g_sign;
	g_v.g_sign = s[0] == '-' ? '-' : g_v.g_sign;
	g_v.minus_flag ? g_v.zero_sign = 0 : 0;
	if (g_v.zero_sign && g_v.precis < 0)
		g_v.width_sign = '0';
	else
		g_v.width_sign = ' ';
	g_v.precis != -1 ? g_v.zero_sign = 0 : 0;
	g_v.plus_sign ? g_v.space_sign = 0 : 0;
	if (!(g_v.type_spec == 'd' || g_v.type_spec == 'i'))
		g_v.g_sign = 0;
	g_v.g_sign_len = g_v.g_sign ? 1 : 0;
	if (g_v.sharp_sign && !ft_strchr("fboxX", g_v.type_spec))
		g_v.sharp_sign = 0;
	if (g_v.sharp_sign && ft_strchr("bxX", g_v.type_spec) && s[0] != '0')
		g_v.width -= 2;
}

void		diouxxb_printer(char *s)
{
	int		len;

	f_exceptions(s);
	if (g_v.g_sign == '-')
		s++;
	if (g_v.sharp_sign && s[0] != '0' && ft_strchr("oxX", g_v.type_spec))
		s = g_v.type_spec == 'o' ? ft_strjoinfree("0",
				(char const *)s, 0, 0) : s;
	if (ft_strchr("xX", g_v.type_spec) && !g_v.precis && s[0] == '0')
		s[0] = 0;
	if (s[0] == '0' && !g_v.precis && !g_v.sharp_sign)
		s[0] = 0;
	len = ft_strlen(s);
	if (g_v.minus_flag)
		print_left_adjusted(s, len);
	else
		print_right_adjusted(s, len);
}
