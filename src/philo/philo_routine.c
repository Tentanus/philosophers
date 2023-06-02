/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 17:47:49 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/02 21:56:58 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

typedef void				(*t_go_action) \
							(t_philo *philo, const int64_t sim_start);

void	go_eat(t_philo *philo, const int64_t sim_start)
{
	int64_t	start_eat;

	pthread_mutex_lock(philo->fork_r);
	philo_queue_message(philo, time_diff_ms(sim_start, time_of_day_ms()), FORK);
	pthread_mutex_lock(philo->fork_l);
	philo_queue_message(philo, time_diff_ms(sim_start, time_of_day_ms()), FORK);
	start_eat = time_of_day_ms();
	philo_queue_message(philo, time_diff_ms(sim_start, start_eat), EAT);
	pthread_mutex_lock(&philo->eating);
	philo->time_last_meal = start_eat;
	philo->nbr_meal_eaten += 1;
	time_sleep_ms(philo->public_data->time_eat - \
			time_diff_ms(start_eat, time_of_day_ms()));
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(&philo->eating);
	philo->status = SLEEP;
}

void	go_sleep(t_philo *philo, const int64_t sim_start)
{
	const int64_t	start_sleep = time_of_day_ms();

	philo_queue_message(philo, time_diff_ms(sim_start, start_sleep), SLEEP);
	time_sleep_ms(philo->public_data->time_sleep - \
		time_diff_ms(start_sleep, time_of_day_ms()));
	philo->status = THINK;
}

//	waiting time for wait on mutex doesn't have to be included 

void	go_think(t_philo *philo, const int64_t sim_start)
{
	const int64_t	start_think = time_of_day_ms();

	philo_queue_message(philo, time_diff_ms(sim_start, start_think), THINK);
	philo->status = EAT;
}

static const t_go_action	g_func[4] = {
[0] = NULL,
[1] = go_eat,
[2] = go_sleep,
[3] = go_think,
};

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	int64_t	sim_start;

	philo = ptr;
	sim_start = philo->public_data->time_start;
	pthread_mutex_lock(&philo->public_data->start);
	pthread_mutex_unlock(&philo->public_data->start);
	philo->time_last_meal = time_of_day_ms();
	if (philo->public_data->err == true)
		return (NULL);
	if (philo->philo_id % 2 == 1)
	{
		go_think(philo, sim_start);
		time_sleep_ms(philo->public_data->time_eat / 2);
	}
	while (1)
	{
		if (philo->public_data->err == true)
			break ;
		g_func[philo->status](philo, sim_start);
	}
	return (NULL);
}
