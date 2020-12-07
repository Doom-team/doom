/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:46:05 by clala             #+#    #+#             */
/*   Updated: 2020/02/20 19:02:43 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define T_BUF_BUFF_SIZE 100
# define C_NRM  "\x1B[0m"
# define C_RED  "\x1B[31m"
# define C_GRN  "\x1B[32m"
# define C_YEL  "\x1B[33m"
# define C_BLU  "\x1B[34m"
# define C_MAG  "\x1B[35m"
# define C_CYN  "\x1B[36m"
# define C_WHT  "\x1B[37m"

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>
# include "./libft.h"

typedef struct			s_var
{
	int					plus_sign;
	int					space_sign;
	int					zero_sign;
	int					sharp_sign;
	int					width;
	int					size_spec;
	int					minus_flag;
	int					params_changed;
	int					precis;
	int					len_format;
	int					type_spec;
	char				g_sign;
	int					g_sign_len;
	char				width_sign;
	int					c_zero;
}						t_var;

typedef struct			s_buf
{
	char				*s;
	int					i;
	int					len;
}						t_buf;

typedef union			u_data
{
	signed char			char_;
	signed short		short_;
	signed int			int_;
	signed long			long_;
	signed long long	llong_;
	unsigned char		uchar_;
	unsigned short		ushort_;
	unsigned int		uint_;
	unsigned long		ulong_;
	unsigned long long	ullong_;
	intmax_t			intmax_;
}						t_data;

t_buf					*g_buf;
t_var					g_v;

int						ft_printf(const char *format, ...);
int						ft_dprintf(int fd, const char *format, ...);
int						ft_vdprintf(int fd, const char *format, va_list *ap);
int						ft_asprintf(char **s, const char *format, ...);
int						ft_vasprintf(char **s, const char *format, va_list *ap);
int						select_type_spec(const char *format, int *i);
int						select_size_spec(const char *format, int *i);
int						handle_format(const char *format, va_list *ap, int *i);
void					printf_f(va_list *ap);
void					printf_cspr(va_list *ap);
void					printf_diouxxb(va_list *ap);
void					diouxxb_printer(char *s);
void					printf_r(va_list *ap);
void					t_buf_free(t_buf **buf);
int						t_buf_write(t_buf *buf, const char *str, int len);
void					t_buf_add_size(t_buf *buf);
t_buf					*t_buf_create(int size);
int						t_buf_len(char *s);
int						f_set_globals_default(void);

#endif
