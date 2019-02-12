/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:46:27 by rkulahin          #+#    #+#             */
/*   Updated: 2018/12/30 11:45:26 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "../libft/libft.h"

# define ABS(value) ((value) < 0 ? -(value) : (value))

typedef struct	s_args
{
	int			flag_minus;
	int			flag_plus;
	int			flag_space;
	int			flag_hash;
	int			flag_zero;
	int			width;
	int			precision;
	int			modifiers;

}				t_args;

int				g_ret;

int				ft_printf(char	const *str, ...);

void			free_line(char *str);

int				ft_find_arg(char const *str, int index);
t_args			*ft_arg_inf(char const *str, int *index);
void			ft_change_mod(int i, int *index, int *flag, int num_mod);
int				ft_find_flag(char const *str, t_args *arg, int index);
int				ft_find_width(char const *str, t_args *arg, int index);
int				ft_find_precision(char const *str, t_args *arg, int index);
int				ft_find_modifiers(char const *str, t_args *arg, int index);
void			ft_bonus(char const *str, t_args *arg, va_list ap, int *i);

void			rec_x(long long value, int b, char *ret, int *i);
void			rec_xx(long long value, int b, char *ret, int *i);
char			*ft_itoa_base_x(long long value, int base);
char			*ft_itoa_base_xx(long long value, int base);

void			rec_x_u(unsigned long long v, unsigned int b, char *r, int *i);
void			rec_xx_u(unsigned long long v, unsigned int b, char *r, int *i);
char			*ft_itoa_base_x_u(unsigned long long value, unsigned int base);
char			*ft_itoa_base_xx_u(unsigned long long value, unsigned int base);

void			ft_arg_print(t_args *arg, char const *str, int *i, va_list ap);

void			ft__print(t_args *arg, int *index, char const *str);

void			ft_s_p(char *str, char *ptr);
void			ft_s_print(t_args *arg, va_list ap, int *index);
void			ft_s_put(char *str);

void			ft_c_print(t_args *arg, va_list ap, int *index);

void			ft_x_mod(t_args *arg, va_list ap, int *index);
void			ft_x_print(t_args *arg, va_list ap);
int				ft_instart_x(char **s, int c, int l);
int				ft_inend_x(char **s, int c, int l);
void			ft_precision_x(char **s, int *l, t_args *arg);
void			ft_xx_mod(t_args *arg, va_list ap, int *index);
void			ft_xx_print(t_args *arg, va_list ap);
void			ft_hx_print(t_args *arg, va_list ap);
void			ft_hhx_print(t_args *arg, va_list ap);
void			ft_lx_print(t_args *arg, va_list ap);
void			ft_llx_print(t_args *arg, va_list ap);
void			ft_hxx_print(t_args *arg, va_list ap);
void			ft_hhxx_print(t_args *arg, va_list ap);
void			ft_lxx_print(t_args *arg, va_list ap);
void			ft_llxx_print(t_args *arg, va_list ap);

void			ft_p_print(t_args *arg, va_list ap, int *len);

void			ft_i_mod(t_args *arg, va_list ap, int *index);
void			ft_i_print(t_args *arg, va_list ap);
void			ft_hi_print(t_args *arg, va_list ap);
void			ft_hhi_print(t_args *arg, va_list ap);
void			ft_li_print(t_args *arg, va_list ap);
void			ft_lli_print(t_args *arg, va_list ap);

void			ft_u_mod(t_args *arg, va_list ap, int *index);
void			ft_u_print(t_args *arg, va_list ap);
void			ft_hu_print(t_args *arg, va_list ap);
void			ft_hhu_print(t_args *arg, va_list ap);
void			ft_lu_print(t_args *arg, va_list ap);
void			ft_llu_print(t_args *arg, va_list ap);

void			ft_o_mod(t_args *arg, va_list ap, int *index);
void			ft_o_print(t_args *arg, va_list ap);
void			ft_ho_print(t_args *arg, va_list ap);
void			ft_hho_print(t_args *arg, va_list ap);
void			ft_lo_print(t_args *arg, va_list ap);
void			ft_llo_print(t_args *arg, va_list ap);
void			ft_precision_o(char **s, int *l, t_args *arg);

#endif
