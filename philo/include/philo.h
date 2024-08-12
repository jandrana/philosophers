/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:41:00 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/12 20:26:44 by ana-cast         ###   ########.fr       */
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
# define OE_DELMTX "\033[1;31m`DESTROY_MUTEX_ERROR'\033[0m"
# define OE_NEWTH "\033[1;31m`NEW_THREAD_CREATION_ERROR'\033[0m"
# define OE_DETTH "\033[1;31m`JOIN/DETATCH_THREAD_ERROR'\033[0m"
# define OE_UNKNOWN "\033[1;31m`UNKNOWN ERROR'\033[0m"

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

typedef uint64_t	t_time;

typedef enum e_input_error
{
	NO_ERROR = 0,
	E_NARGS = 1,
	E_NOTPOS = -1,
	E_OORL = -2,
	E_NAN = -3,
}	t_input_error;

typedef enum e_error
{
	E_TIME = 4,
	E_INITMTX = 5,
	E_DELMTX = 6,
	E_NEWTH = 7,
	E_DETTH = 8,
	E_NOMEM = 12,
}	t_error;

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
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork;
	pthread_t		*p_th;
	pthread_mutex_t	*p_lck;
	pthread_mutex_t	deadlock;
}	t_threads;

typedef struct s_philo
{
	int				id;
	int				meals;
	t_time			hunger;
	t_action		status;
	struct s_data	*data;
	t_threads		*th;
}	t_philo;

typedef struct s_data
{
	char			**args;
	int				*info;
	int				stop;
	t_time			start;
	int				ready;
	struct timeval	t_start;
	t_philo			*philos;
	t_threads		*th;
	int				error;
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
void		init_threads(t_data *data, int num_ph);
void		init_philos(t_data	*data);

// ---------------------- ERROR.C ----------------------- //
int			check_parsing(t_data *data);
int			print_error(t_error type, int n_err);

// -------------------- FREE_UTILS.C -------------------- //
char		*free_str(char **str);
void		free_array(char ***array);
void		free_data(t_data **data);
void		*safe_calloc(size_t size, void *dst);
void		destroy_structs_mutex(t_data *data);
void		exit_philo(t_data **data, int error);

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
uint64_t	time_ms(uint64_t start);
int			my_usleep(uint64_t sleep);

// ----------------------- LIBFT.C ---------------------- //
void		philo_strcpy(char *dst, const char *src, int len);
long		ft_atoui(char *str);

void		start_threads(t_data *data);
void		fight_for_forks(t_philo *philo);
void		share_forks_and_rest(t_philo *philo);
void		spaguetti_time(t_philo *philo);
void		rest_happily(t_philo *philo);
void		increase_wisdom(t_philo *philo);

uint64_t	time_ts(struct timeval t_start);

#endif /* PHILO_H */
