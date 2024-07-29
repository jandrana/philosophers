/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:41:00 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/29 19:42:30 by ana-cast         ###   ########.fr       */
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
	E_NOMEM = 12
}	t_type_error;

// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //

// ------------------------------------------------------ //
//                      UTILS FOLDER                      //
// ------------------------------------------------------ //

// ---------------------- ERROR.C ----------------------- //

// -------------------- FREE_UTILS.C -------------------- //

// ------------------- STRUCT_NODE.C -------------------- //

// ------------------- PRINT_UTILS.C -------------------- //

// ----------------------- UTILS.C ---------------------- //

#endif /* PHILO_H */