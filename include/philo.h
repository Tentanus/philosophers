/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:26:08 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/26 21:09:40 by mweverli      ########   odam.nl         */
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
	int32_t				nbr_philo;
	int32_t				nbr_full_philo;
	int32_t				nbr_meal;
	int32_t				time_die;
	int32_t				time_eat;
	int32_t				time_sleep;
	int64_t				time_start;
	pthread_mutex_t		start;
	bool				death;
}	t_public;

typedef struct	s_queue{
	int32_t				*time[2];
	int32_t				*philo[2];
	int32_t				*action[2];
	int32_t				count;
	pthread_mutex_t		msg_mutex;
}	t_queue;

typedef struct s_philo {
	pthread_t			*thread;
	int32_t				philo_id;
	int32_t				nbr_meal_eaten;
	unsigned long		time_last_meal;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*fork_l;
	const t_public		*public_data;
	t_queue				queue;
}	t_philo;

typedef enum e_message {
	SUCCESS,
	ERR_ARG,
	ERR_INP,
	ERR_MEM,
	ERR_THR,
}	t_message;

//	FUNCTIONS

int32_t	philo_init(char **argv, t_public *info);
int32_t	philo_alloc(t_public *info, t_philo **philos);

void	philo_alloc_free(t_philo *philos, pthread_mutex_t *forks, size_t limit);

//		UTILS
//		utils: convert
int32_t	ph_atoi(char *inp);

//		utils: error 
int32_t	philo_error(int32_t code);

//		utils: memory
void	*ph_memset(void *ptr, int c, size_t len);
void	*ph_calloc(size_t byte, size_t size);

//		utils: string 
int32_t	ph_strlen(const char *inp);
void	ph_putstr_fd(const int fd, const char *str);
void	ph_putendl_fd(const int fd, const char *str);


#endif
