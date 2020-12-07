/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 11:06:24 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	case_two(int c, char *b, int *on)
{
	*b++ = 192 + c / 64;
	*b++ = 128 + c % 64;
	*on = 2;
}

static void	case_three(int c, char *b, int *on)
{
	*b++ = 224 + c / 4096;
	*b++ = 128 + c / 64 % 64;
	*b++ = 128 + c % 64;
	*on = 3;
}

static void	case_four(int c, char *b, int *on)
{
	*b++ = 240 + c / 262144;
	*b++ = 128 + c / 4096 % 64;
	*b++ = 128 + c / 64 % 64;
	*b++ = 128 + c % 64;
	*on = 4;
}

void		ft_putwchar_fd(int out, int c)
{
	int		on;
	char	s[4];
	char	*b;

	on = 0;
	b = &s[0];
	if (sizeof(c) == 4)
	{
		if (c < 0x80)
		{
			*b++ = c;
			on = 1;
		}
		else if (c < 0x800)
			case_two(c, b, &on);
		else if (c - 0xd800u < 0x800)
			return ;
		else if (c < 0x10000)
			case_three(c, b, &on);
		else if (c < 0x110000)
			case_four(c, b, &on);
	}
	if (on > 0)
		write(out, &s, on);
}
