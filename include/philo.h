/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:26:08 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/23 16:58:59 by mweverli      ########   odam.nl         */
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
# include <stdbool.h>

//		PERSONAL INCLUDES
# include <stdio.h>

//	DEFINES

# define ERROR -1

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD "died"

//	STRUCTURES AND ENUMS
typedef struct s_public {
	int32_t				n_philo;
	int32_t				n_meal;
	int32_t				t_die;
	int32_t				t_eat;
	int32_t				t_sleep;
	int32_t				n_full_philo;
	bool				death;
	unsigned long		t_start;
	pthread_mutex_t		*fork;
}	t_public;

typedef struct s_philo {
	int32_t				id;
	int32_t				n_meal_eaten;
	pthread_mutex_t		fork_l;
	pthread_mutex_t		fork_r;
	unsigned long		t_last_eaten;
}	t_philo;

typedef enum e_message {
	SUCCESS,
	ERR_ARG,
	ERR_INP,
	ERR_MEM,
	ERR_THR,
}	t_message;

//	FUNCTIONS

int32_t			philo_error(int32_t code);

int32_t			philo_init(char **argv, t_public *info);
int32_t			philo_alloc(t_public *info, pthread_t **philo);

//		UTILS

//		utils: string 
int32_t		ph_strlen(const char *inp);
void		ph_putstr_fd(const int fd, const char *str);
void		ph_putendl_fd(const int fd, const char *str);

//		utils: convert
int32_t		ph_atoi(char *inp);

//		utils: memory
void		*ph_calloc(size_t byte, size_t size);


#endif
