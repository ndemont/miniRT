/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:16:03 by ndemont           #+#    #+#             */
/*   Updated: 2020/12/01 17:27:16 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>

typedef struct	s_conversion
{
	char		*listcv;
	int			*checkcv;
	char		*listfg;
	int			*checkfg;
}				t_conversion;

typedef struct	s_flags
{
	int			minus;
	int			zero;
	int			plus;
	int			hash;
}				t_flags;

typedef struct	s_width
{
	int			num;
	int			value;
	int			star;
}				t_width;

typedef struct	s_precision
{
	int			period;
	int			star;
	int			value;
}				t_precision;

typedef struct	s_size
{
	int			h;
	int			l;
}				t_size;

typedef	struct	s_type
{
	char		letter;
}				t_type;

typedef struct	s_printf
{
	t_flags		flags;
	t_width		width;
	t_precision	precision;
	t_size		size;
	t_type		type;
}				t_printf;

typedef struct	s_conv_list
{
	char		*type;
	int			*value;
}				t_conv_list;

int				ft_printf(const char *s, ...);

void			ft_putchar_n_fd(char c, int n);
int				ft_intlen(int unit, long n);

void			ft_putpointer_xmin_fd(void *p, int fd);
void			ft_putpointer_xmaj_fd(void *p, int fd);
void			ft_puthex_min_fd(long n, int fd);
void			ft_puthex_maj_fd(long n, int fd);

void			ft_init_flags(t_printf *elem);
void			ft_init_width(t_printf *elem);
void			ft_init_precision(t_printf *elem);
void			ft_init_type(t_printf *elem);
void			ft_init_elem(t_printf *elem);

int				ft_check_flags(const char *s, t_printf *elem, int i);
int				ft_check_width(const char *s, t_printf *elem, int i);
int				ft_check_precision(const char *s, t_printf *elem, int i);
int				ft_check_type(const char *s, t_printf *elem, int i);

int				ft_set_flags(char c, t_printf *elem);
int				ft_set_field(char c, t_printf *elem);
int				ft_set_precision(char c, t_printf *elem);
int				ft_set_type(char c, t_printf *elem);
int				ft_set_elem(const char *s, t_printf *elem);

int				ft_putchar_conv(va_list ap, t_printf *elem);
int				ft_putper_conv(va_list ap, t_printf *elem);
int				ft_putpointer_conv(va_list ap, t_printf *elem);
int				ft_putstr_conv(va_list ap, t_printf *elem);
int				ft_putint_conv(va_list ap, t_printf *elem);
int				ft_putuint_conv(va_list ap, t_printf *elem);
int				ft_puthex_min_conv(va_list ap, t_printf *elem);
int				ft_puthex_maj_conv(va_list ap, t_printf *elem);
void			ft_set_flags_conv_u(t_printf *elem, int *len, int *width,\
				int *prec);

int				ft_select_conversion(va_list ap, t_printf *elem);
int				ft_check_conversion(t_printf *elem, va_list ap);

#endif
