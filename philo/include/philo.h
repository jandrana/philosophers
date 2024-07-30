/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:41:00 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/30 20:55:48 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// ------------------- EXT LIBRARIES ------------------- //

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

// ------------------ COLOR MACROS ------------------ //

# define WHITE "\033[0m"
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define TURQUOISE "\033[36m"

// ------------------- STRUCTURES ------------------- //

typedef enum e_type_redir
{
	INFILE = 10,
	APPEND = 11,
	OUTFILE = 12,
	HEREDOC = 13,
	NOT_REDIR = -1
}	t_type_redir;

typedef enum e_type_error
{
	E_NARGS = 1,
	E_NOTPOS = 2,
	E_NEG = 3,
	E_OPT = 4,
	E_NOMEM = 12
}	t_type_error;

typedef struct s_input
{
	ssize_t	n_philos;
	ssize_t	t_die;
	ssize_t	t_eat;
	ssize_t	t_sleep;
	ssize_t	n_philo_eat;
	ssize_t	t_start;
	int		err_data;
}	t_input;

// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //
t_input	*parse_input(int argc, char **input);

// ------------------------------------------------------ //
//                      UTILS FOLDER                      //
// ------------------------------------------------------ //

// ---------------------- ERROR.C ----------------------- //

// -------------------- FREE_UTILS.C -------------------- //

// ------------------- STRUCT_NODE.C -------------------- //

// ------------------- PRINT_UTILS.C -------------------- //

// ----------------------- UTILS.C ---------------------- //

#endif /* PHILO_H */