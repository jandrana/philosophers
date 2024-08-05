/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:41:00 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/05 20:33:18 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// -------------------- EXT LIBRARIES ------------------- //

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>

// -------------------- COLOR MACROS -------------------- //

# define WHITE "\033[0m"
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define TURQUOISE "\033[36m"

// ---------------- OUTPUT ERROR MACROS ----------------- //

# define OE_NARGS "\033[1;33m`MISSING_ARGS'\033[0m"
# define OE_MARGS "\033[1;31m`TOO_MANY_ARGS' (max 5)\033[0m"
# define OE_NOTPOS "\033[1;31m`NOT_A_POSITIVE_NUMBER'\033[0m"
# define OE_OORL "\033[1;31m`OUT_OF_RANGE'\033[0m"
# define OE_NAN "\033[1;31m`NOT_A_NUMBER'\033[0m"
# define OE_NOMEM "\033[1;31m`OUT_OF_MEMORY'\033[0m"

# define ON_PHILOS "num_philos "
# define OT_DIE "time_to_die "
# define OT_EAT "time_to_eat "
# define OT_SLEEP "time_to_sleep "
# define ONT_EAT "[num_times_each_must_eat] "

// --------------------- STRUCTURES --------------------- //

typedef enum e_type_error
{
	NO_ERROR = 0,
	E_NARGS = 1,
	E_NOTPOS = -1,
	E_OORL = -2,
	E_NAN = -3,
	E_NOMEM = 12
}	t_type_error;

typedef enum e_n_input
{
	N_PHILOS = 0,
	T_DIE = 1,
	T_EAT = 2,
	T_SLEEP = 3,
	NT_EAT = 4,
	NO_ARG = -1
}	t_n_input;

typedef enum e_action
{
	THINK = 0,
	EAT = 1,
	SLEEP = 2,
	DEAD = 3
}	t_action;

typedef struct s_philos
{
	int				id;
	long long		death;
	int				action;
	int				nb_eat;
	pthread_mutex_t	lock;
	pthread_mutex_t	*left_fk;
	pthread_mutex_t	*right_fk;
	struct s_philos	*next;
	struct s_philos	*prev;
}	t_philos;

typedef struct s_input
{
	int		n_philos;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		nt_eat;
	int		t_start;
	char	**input;
	int		errors;
}	t_input;

// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //
int		check_data(t_input	*data, int pos);
int		parse_input(int argc, char **argv, t_input *data);

// ------------------------------------------------------ //
//                      UTILS FOLDER                      //
// ------------------------------------------------------ //

// ---------------------- INIT.C ----------------------- //
t_input	*init_data(void);

// ---------------------- ERROR.C ----------------------- //
int		put_error(t_input *data, t_type_error type);

// -------------------- FREE_UTILS.C -------------------- //
char	*free_str(char **str);
void	free_array(char ***array);

// --------------------- PH_SPLIT.C --------------------- //
char	**ph_split(char const *s, char c);

// ------------------- PRINT_UTILS.C -------------------- //
void	print_input(t_input *input);

// ----------------------- UTILS.C ---------------------- //
char	*ft_substr(const char *str, ssize_t start, ssize_t len);
int		ft_strlen(const char *str);
char	*ft_strdup(char *s1);
int		array_len(char **array);
bool	in_range(ssize_t value, ssize_t min, ssize_t max);

// ----------------------- LIBFT.C ---------------------- //
void	philo_strcpy(char *dst, const char *src, int len);
long	ft_atoui(char *str);

#endif /* PHILO_H */