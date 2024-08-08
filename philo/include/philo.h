/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:41:00 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/08 19:55:41 by ana-cast         ###   ########.fr       */
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
# define OE_TIME "\033[1;31m`gettimeofday()'\033[0m"
# define OE_INITMTX "\033[1;31m`INIT_MUTEX_ERROR'\033[0m"
# define OE_DELMTX "\033[1;31m`DETATCH_MUTEX_ERROR'\033[0m"
# define OE_NEWTH "\033[1;31m`NEW_THREAD_CREATION_ERROR'\033[0m"

# define ON_PHILOS "num_philos "
# define OT_DIE "time_to_die "
# define OT_EAT "time_to_eat "
# define OT_SLEEP "time_to_sleep "
# define ONT_EAT "[num_times_each_must_eat] "

# define O_THINK " is thinking\n"
# define O_FORK " has taken a fork\n"
# define O_EAT " is eating\n"
# define O_SLEEP " is sleeping\n"
# define O_DEAD " died\n"

// --------------------- STRUCTURES --------------------- //

typedef enum e_type_error
{
	NO_ERROR = 0,
	E_NARGS = 1,
	E_NOTPOS = -1,
	E_OORL = -2,
	E_NAN = -3,
	E_TIME = 4,
	E_INITMTX = 5,
	E_DELMTX = 6,
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
	FORK = 1,
	EAT = 2,
	SLEEP = 3,
	DEAD = 4
}	t_action;

typedef struct s_threads
{
	pthread_t		data;
	pthread_t		*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	lock;
	pthread_mutex_t	*ph_lock;
	pthread_mutex_t	*fork;
}	t_threads;

typedef struct s_philo
{
	int				id;
	int				meals;
	uint32_t		hunger;
	t_action		status;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	char		**args;
	int			*info;
	int			stop;
	uint64_t	start;
	t_philo		*philos;
	t_threads	*threads;
	int			error;
}	t_data;

// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //
int			check_args(t_data *data, int pos);
void		parse_input(int argc, char **argv, t_data *data);

// ------------------------------------------------------ //
//                      UTILS FOLDER                      //
// ------------------------------------------------------ //

// ---------------------- INIT.C ----------------------- //
t_data		*init_data(void);
void		init_philos(t_data	*data);

// ---------------------- ERROR.C ----------------------- //
int			check_parsing(t_data *data);
int			print_error(t_type_error type, int errno);

// -------------------- FREE_UTILS.C -------------------- //
char		*free_str(char **str);
void		free_array(char ***array);
void		free_data(t_data **data);
void		*safe_calloc(size_t size, void *dst);
void		exit_philo(t_data **data, t_type_error error);

// --------------------- PH_SPLIT.C --------------------- //
char		**ph_split(char const *s, char c);

// ------------------- PRINT_UTILS.C -------------------- //
void		print_input(t_data *data);
char		*get_action_msg(int action);
void		print_status(t_philo *wise_man, int action);

// ----------------------- UTILS.C ---------------------- //
char		*ft_substr(const char *str, ssize_t start, ssize_t len);
int			ft_strlen(const char *str);
char		*ft_strdup(char *s1);
int			array_len(char **array);
bool		in_range(ssize_t value, ssize_t min, ssize_t max);
uint64_t	get_time_ms(uint64_t start);
int			my_usleep(uint64_t sleep);
int			ft_strncmp(char *s1, char *s2, size_t n);

// ----------------------- LIBFT.C ---------------------- //
void		philo_strcpy(char *dst, const char *src, int len);
long		ft_atoui(char *str);

#endif /* PHILO_H */
