/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:26:08 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/01 18:32:22 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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
	bool				err;
}	t_public;

typedef struct s_msg_queue{
	int32_t				*time[2];
	int32_t				*philo[2];
	int32_t				*action[2];
	int32_t				count;	// mutexed
	pthread_mutex_t		msg_mutex;
}	t_msg_queue;

typedef struct s_philo {
	pthread_t			*thread;
	int32_t				philo_id;
	int32_t				nbr_meal_eaten;
	int32_t				status;
	int64_t				time_last_meal;
	pthread_mutex_t		*fork_r;
	pthread_mutex_t		*fork_l;
	t_public			*public_data;
	t_msg_queue			*queue;
}	t_philo;

typedef enum e_msg {
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
	END
}	t_msg;

typedef enum e_err_msg {
	SUCCESS,
	ERR_ARG,
	ERR_INP,
	ERR_MEM,
	ERR_THR,
}	t_err_msg;

//	FUNCTIONS

int32_t	philo_init(char **argv, t_public *info);
int32_t	philo_alloc(t_public *info, t_philo **philos, t_msg_queue *queue);
int32_t	philo_run(t_public *info, t_philo *philos, t_msg_queue *queue);
void	philo_printer(t_msg_queue *queue);

void	*philo_routine(void *ptr);

void	philo_queue_message(t_philo *philo, int64_t time, t_msg msg);

int32_t	philo_error(int32_t code);

void	philo_free_alloc(t_philo *philos, pthread_mutex_t *forks, size_t limit);
void	philo_free_queue(t_msg_queue *queue);
void	philo_thread_join(t_philo *philos, size_t max_philos);

//		UTILS
//		utils: convert
int32_t	ph_atoi(char *inp);

//		utils: memory
void	*ph_memset(void *ptr, int c, size_t len);
void	*ph_calloc(size_t byte, size_t size);

//		utils: string 
int32_t	ph_strlen(const char *inp);
void	ph_putstr_fd(const int fd, const char *str);
void	ph_putendl_fd(const int fd, const char *str);

//		utils: time
void	time_sleep_ms(int64_t sleep_ms);
int64_t	time_diff_ms(int64_t start, int64_t end);
int64_t	time_of_day_ms(void);

#endif
