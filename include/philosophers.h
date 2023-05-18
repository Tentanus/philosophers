/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:26:08 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/18 19:34:48 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//	INCLUDE

# include <unistd.h>		// usleep,
# include <stdlib.h>		// write,
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
typedef struct s_public {
	int32_t	n_philo;
	int32_t	n_meal;
	int32_t	t_die;
	int32_t	t_eat;
	int32_t	t_sleep;
}	t_public;

typedef enum e_message {
	SUCCESS,
	ARGUMENTS,
	INPUT
}	t_message;

//	FUNCTIONS

int32_t			philo_init(char **argv, t_public *info);
int32_t			philo_error(int32_t code);

//		UTILS

void		ph_putstr_fd(const int fd, const char *str);
void		ph_putendl_fd(const int fd, const char *str);
size_t		ph_atoi(char *inp);

#endif
