/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:41:00 by ana-cast          #+#    #+#             */
/*   Updated: 2024/08/15 21:20:57 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// -------------------- EXT LIBRARIES ------------------- //

# include <string.h>
# include <stdio.h>
# include <stdlib.h> 	// IWYU pragma: keep
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>	// IWYU pragma: keep
# include <errno.h>  	// IWYU pragma: keep

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


// ------------- OUTPUT PHILO ACTION MACROS ------------- //

# define O_THINK "is thinking\n"
# define O_FORK "has taken a fork\n"
# define O_EAT "is eating\n"
# define O_SLEEP "is sleeping\n"
# define O_DEAD "died\n"



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

// ------------- SEMAPHORES NAME MACROS ------------- //

# define SEM_FORK "/fork"
# define SEM_START "/start"
# define SEM_STOP "/stop"
# define SEM_READY "/ready"	//think again about this one
# define SEM_PRINT "/print"
# define SEM_EAT "/eating"

typedef struct s_philo
{
	int				id;
	t_time			hunger;
	t_action		status; // not needed after implementing sem_t *eating
	int				meals; // check if needed after implementing sem_t *ready
	sem_t			*eat;	// indicates if philo is currently eating 
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	char			**args;
	int				*info;
	pid_t			*pid;
	sem_t			*forks;
	sem_t			*start;	// think again about this one
	sem_t			*stop;	// think again about this one
	sem_t			*ready;	// think again about this one
	sem_t			*print;
	struct timeval	t_start;
	t_philo			*philos;
	int				error;
}	t_data;

// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //
int			check_args(t_data *data, int pos);
void		expected_death(t_data *data);

// --------------------- THREADS.C ---------------------- //
void		start_threads(t_data *data);
void		*satisfaction_monitor(void *v_data);
void		*schrodinger_monitor(void *v_philo);

// ------------------- PHILO_ROUTINES.C ----------------- //
void		routine(t_philo	*philo);

// ------------------------------------------------------ //
//                      PARSER FOLDER                     //
// ------------------------------------------------------ //

// ------------------- PARSE_INPUT.C -------------------- //
void		parse_input(int argc, char **argv, t_data *data);

// ---------------------- ERROR.C ----------------------- //
int			check_parsing(t_data *data);
int			print_error(t_error type, int n_err);

// ------------------------------------------------------ //
//                      UTILS FOLDER                      //
// ------------------------------------------------------ //

// ---------------------- INIT.C ----------------------- //
t_data		*init_data(void);
void		init_threads(t_data *data, int num_ph);
void		init_philos(t_data	*data);

// ----------------------- LIBFT.C ---------------------- //
int			ft_strlen(const char *str);
char		*ft_strdup(char *s1);
char		*ft_substr(const char *str, ssize_t start, ssize_t len);
long		ft_atoui(char *str);

// ----------------------- SPLIT.C ---------------------- //
char		**split(char const *s, char c);

// ------------------ THREADS_UTILS.C ------------------- //
void		perform_routine(t_philo *philo);
t_time		print_status(t_philo *wise_man, int action);

// --------------------- SAFE_EXIT.C -------------------- //
void		free_array(char ***array);
void		free_data(t_data **data);
void		*safe_calloc(size_t size, void *dst);
void		destroy_structs_mutex(t_data *data);
void		exit_philo(t_data **data, int error);

// ----------------------- UTILS.C ---------------------- //
int			array_len(char **array);
bool		in_range(ssize_t value, ssize_t min, ssize_t max);
uint64_t	time_ts(struct timeval t_start);
int			my_usleep(t_time sleep, t_time current, struct timeval t_start);

#endif /* PHILO_BONUS_H */
