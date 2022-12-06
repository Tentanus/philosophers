/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:26:08 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/06 22:17:29 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//	INCLUDE

# include <unistd.h>		// usleep,
# include <stdlib.h>
# include <sys/time.h>		// gettimeofday, 
# include <pthread.h>		// pthread_(creat, detach, join, mutex_init, mutex_destroy, mutex_lock, mutex_unlock)
# include <stdlib.h>		// write,
# include <limits.h>

//		PERSONAL INCLUDES

//	STRUCTURES
typedef struct s_philo {
	uint32_t	n_philo;
	uint32_t	t_die;
	uint32_t	t_eat;
	uint32_t	t_sleep;
	uint32_t	n_meal;
}	t_philo;


//	FUNCTIONS

t_philo	philo_init(char**argv);
void	philo_error(void);

#endif
