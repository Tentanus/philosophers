/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 17:47:49 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/30 12:05:59 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

typedef void	(*go_func) (t_philo *philo);

void	go_eat(t_philo *philo) 
{
	philo = NULL;
}

void	go_sleep(t_philo *philo) 
{
	philo = NULL;
}

void	go_think(t_philo *philo) 
{
	philo = NULL;
}

static const go_func f[4] = {
	[0] = NULL,
	[1] = go_eat,
	[2] = go_sleep,
	[3] = go_think,
} ;

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	pthread_mutex_lock(&philo->public_data->start);
	pthread_mutex_unlock(&philo->public_data->start);
	philo->time_last_meal = time_of_day_ms();
	if (philo->public_data->err == true)
		return (NULL);
	if (philo->philo_id % 2 == 1)
		go_think(philo);
	while (1)
	{
		if (philo->status == DIE || philo->status == END)
			break ;
		f[philo->status](philo);
	}
	return (NULL);
}
