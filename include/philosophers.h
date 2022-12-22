/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:26:08 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/22 15:36:32 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//	INCLUDE

# include <unistd.h>		// usleep,
# include <stdlib.h>		// write, :w

# include <sys/time.h>		// gettimeofday, 
# include <pthread.h>
//int	pthread_detach
//int	pthread_join
//int	pthread_mutex_destroy
//int	pthread_mutex_init
//int	pthread_mutex_lock
//int	pthread_mutex_unlock
# include <stdlib.h>
# include <limits.h>

//		PERSONAL INCLUDES
# include <stdio.h>

//	DEFINES

# define ERROR -1

//	STRUCTURES AND ENUMS
typedef struct s_philo {
	int32_t	n_philo;
	int32_t	t_die;
	int32_t	t_eat;
	int32_t	t_sleep;
	int32_t	n_meal;
}	t_philo;

typedef struct s_shared {
	bool	death;
	bool	start;
	bool	error;

}	t_shared;
typedef enum e_message {
	SUCCESS,
	ARGUMENTS,
	INPUT
}	t_message;

//	FUNCTIONS

int32_t		philo_init(char**argv);
int			philo_error(int code);

//		UTILS

void		ph_putendl_fd(const char *str, int fd);
size_t		ph_atoi(char *inp);

#endif
