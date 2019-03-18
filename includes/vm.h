/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkulahin <rkulahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 12:21:40 by rkulahin          #+#    #+#             */
/*   Updated: 2019/03/18 11:11:38 by rkulahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libftprintf/includes/ft_printf.h"
# include <fcntl.h>
# include "op.h"
# include "ncurses.h"

/*
** color types
*/

# define EOC "\033[0m"

# define RED "\033[1;31m"
# define GRE "\033[32m"
# define BLU "\033[34m"
# define YEL "\033[1;33m"
# define VIO "\033[35m"
# define BLA "\033[30m"
# define WHI "\033[1;37m"

typedef struct s_vm			t_vm;
typedef struct s_players	t_players;
typedef struct s_carriage	t_carriage;
struct						s_players
{
	int						index;
	int						live;
	t_header				*champ;
	t_players				*next;
};
struct						s_vm
{
	int						index_player[MAX_PLAYERS];
	int						nbr_cycles;
	int						nbr_plrs;
	int						cycle;
	int						live;
	int						nbr_checks;
	int						cycle_to_die;
	int						die;
	int						nbr_log;
	int						aff;
	int						curses;
	int						nbr_car;
	unsigned char			map[MEM_SIZE * 2];
	unsigned char			color[MEM_SIZE * 2];
	t_players				*players;
	int						last_index;
	char					*last_name;
	t_carriage				*carriage;
};

struct						s_carriage
{
	int						position;
	int						carry;
	int						nbr_plr;
	int						index;
	unsigned int			regist[REG_NUMBER];
	int						live;
	char					operation[2];
	int						cycle;
	t_carriage				*next;
	t_carriage				*prev;
};

/*
** main.c
*/
t_vm						*init_vm(void);
t_players					*init_player(void);
void						error(char *line);
unsigned int				reverse(unsigned int b);
/*
** parce.c
*/
t_vm						*parce_argv(int ac, char **av, int i);
t_header					*parce_champ(int fd, unsigned int i,
char *s, char *s1);
void						add_champ(t_vm **all, t_players *new);
void						parce_champ_index(t_vm *all);
void						put_champ_index(t_vm *all);
/*
** valid.c
*/
int							valid_champ(t_vm *all, char **av, int i);
int							valid_num(t_vm *all, int ac, char **av, int i);
int							valid_dump(t_vm *all, int ac, char **av,
int i);
int							str_of_num(char *str);
int							nbr_champ(t_players *tmp);
/*
** vm_map.c
*/
void						vm_map(t_vm *vm, t_players *plr, int i, int k);
void						add_carriage(t_vm *vm, t_carriage *new);
void						init_carriage(t_vm *vm, int index, int position);
/*
** corewar.c
*/
void						kill_carriage(t_vm *vm, t_carriage **cr);
void						main_check(t_vm *vm, t_carriage *tmp);
void						check_player(t_vm *vm);
void						check_command(t_vm *vm, t_carriage *cr);
void						main_cycle(t_vm *vm);
void						change_cycle(t_vm *vm);
int							check_new_command(t_vm *vm, t_carriage *cr);
/*
** func.c
*/
int							vm_atoi_16(char *a1);
char						*vm_itoa_16(long long numb);
int							*check_arg(int nb);
/*
** other.c
*/
void						print_dump(t_vm *vm);
void						win_player(t_vm *vm, t_players *last);
void						replace_map(t_vm *vm, int position,
char *ptr, int nb);
void						privetstvie(t_vm *vm);

/*
** op_live.c
*/
void						op_live(t_vm *vm, t_carriage *cr);
char						*valid_str(t_vm *vm, int position, int	nb);
/*
** op_fork.c
*/
void						copy_regist(t_carriage *new, t_carriage *cr);
t_carriage					*copy_carriage(t_vm *vm, t_carriage *cr);
void						op_fork(t_vm *vm, t_carriage *cr);
void						op_lfork(t_vm *vm, t_carriage *cr);
/*
** op_st.c
*/
void						op_st(t_vm *vm, t_carriage *cr);
void						op_sti(t_vm *vm, t_carriage *cr);
/*
** op_and.c
*/
void						op_and(t_vm *vm, t_carriage *cr);
/*
** op_or.c
*/
void						op_or(t_vm *vm, t_carriage *cr);
/*
** op_xor.c
*/
void						op_xor(t_vm *vm, t_carriage *cr);
/*
** op_add.c
*/
void						op_add(t_vm *vm, t_carriage *car);
void						op_sub(t_vm *vm, t_carriage *car);

/*
** op_aff.c
*/
void						op_aff(t_vm *vm, t_carriage *cr);

/*
** op_load_index.c
*/
void						op_load_index(t_vm *vm, t_carriage *cr);

/*
** op_load.c
*/
void						op_load(t_vm *vm, t_carriage *cr);
/*
** op_long_load_index.c
*/
void						op_long_load_index(t_vm *vm, t_carriage *cr);

/*
** op_zjmp.c
*/
void						op_zjmp(t_vm *vm, t_carriage *cr);

/*
** op_long_load.c
*/
void						op_long_load(t_vm *vm, t_carriage *car);

/*
** bonus_parce.c
*/
int							valid_log(t_vm *all, int ac, char **av, int i);
int							valid_aff(t_vm *all, int i);
int							valid_curses(t_vm *all, int i);
void						print_usage(void);
void						null_flags(t_vm *vm);
void						print_sti(int *t_args, t_carriage *cr);
void						print_v4(t_carriage *cr, int *ar);
void						print_lldi(t_carriage *cr, int *ar);
void						visual_map(t_vm *vm);
void						init_curses(t_vm *vm);
void						recolor_map(t_vm *vm, int position,
int nb, int color);
void						delete_cr(t_vm *vm);
void						print_cr(t_vm *vm);
void						visual_menu(t_vm *vm, int sleep, int i);
void						prnt_instruction(void);
int							control_curses(int vis, t_vm *vm, int key);
typedef	void				(*t_func)(t_vm *vm, t_carriage *cr);
extern	t_func				g_func[17];
#endif
