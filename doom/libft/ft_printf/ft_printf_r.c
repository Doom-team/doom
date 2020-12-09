/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:46:37 by clala             #+#    #+#             */
/*   Updated: 2020/02/20 18:59:05 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	print_twenty_to_thirty_n_last(char c)
{
	if (c == 21)
		t_buf_write(g_buf, "[NAK]", 5);
	else if (c == 22)
		t_buf_write(g_buf, "[SYN]", 5);
	else if (c == 23)
		t_buf_write(g_buf, "[ETB]", 5);
	else if (c == 24)
		t_buf_write(g_buf, "[CAN]", 5);
	else if (c == 25)
		t_buf_write(g_buf, "[EM]", 4);
	else if (c == 26)
		t_buf_write(g_buf, "[SUB]", 5);
	else if (c == 27)
		t_buf_write(g_buf, "[ESC]", 5);
	else if (c == 28)
		t_buf_write(g_buf, "[FS]", 4);
	else if (c == 29)
		t_buf_write(g_buf, "[GS]", 4);
	else if (c == 30)
		t_buf_write(g_buf, "[RS]", 4);
	else if (c == 31)
		t_buf_write(g_buf, "[US]", 4);
	else if (c == 127)
		t_buf_write(g_buf, "[DEL]", 5);
}

static void	print_ten_to_twenty(char c)
{
	if (c == 11)
		t_buf_write(g_buf, "[VT]", 5);
	else if (c == 12)
		t_buf_write(g_buf, "[FF]", 4);
	else if (c == 13)
		t_buf_write(g_buf, "[CR]", 4);
	else if (c == 14)
		t_buf_write(g_buf, "[SO]", 4);
	else if (c == 15)
		t_buf_write(g_buf, "[SI]", 4);
	else if (c == 16)
		t_buf_write(g_buf, "[DLE]", 5);
	else if (c == 17)
		t_buf_write(g_buf, "[DC1]", 5);
	else if (c == 18)
		t_buf_write(g_buf, "[DC2]", 5);
	else if (c == 19)
		t_buf_write(g_buf, "[DC3]", 5);
	else if (c == 20)
		t_buf_write(g_buf, "[DC4]", 5);
}

static void	print_zero_to_ten(char c)
{
	if (c == 0)
		t_buf_write(g_buf, "[NUL]", 5);
	else if (c == 1)
		t_buf_write(g_buf, "[SOH]", 5);
	else if (c == 2)
		t_buf_write(g_buf, "[STX]", 5);
	else if (c == 3)
		t_buf_write(g_buf, "[ETX]", 5);
	else if (c == 4)
		t_buf_write(g_buf, "[EOT]", 5);
	else if (c == 5)
		t_buf_write(g_buf, "[ENQ]", 5);
	else if (c == 6)
		t_buf_write(g_buf, "[ACK]", 5);
	else if (c == 7)
		t_buf_write(g_buf, "[BEL]", 5);
	else if (c == 8)
		t_buf_write(g_buf, "[BS]", 4);
	else if (c == 9)
		t_buf_write(g_buf, "[TAB]", 5);
	else if (c == 10)
		t_buf_write(g_buf, "[LF]", 4);
}

void		printf_r(va_list *ap)
{
	int		i;
	char	*s;

	s = va_arg(*ap, char *);
	i = 0;
	while (s[i])
	{
		if (s[i] >= 0 && s[i] <= 10)
			print_zero_to_ten(s[i]);
		else if (s[i] >= 11 && s[i] <= 20)
			print_ten_to_twenty(s[i]);
		else if ((s[i] >= 21 && s[i] <= 31) || s[i] == 127)
			print_twenty_to_thirty_n_last(s[i]);
		i++;
	}
	print_zero_to_ten(s[i]);
}
