/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_actions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 19:35:37 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/05 19:49:22 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	go_eat(t_philo *philo, const int64_t sim_start)
{
	int64_t	start_eat;

	pthread_mutex_lock(philo->fork_r);
	philo_queue_message(philo, time_diff_ms(sim_start, time_of_day_ms()), FORK);
	pthread_mutex_lock(philo->fork_l);
	philo_queue_message(philo, time_diff_ms(sim_start, time_of_day_ms()), FORK);
	pthread_mutex_lock(&philo->eating);
	start_eat = time_of_day_ms();
	philo_queue_message(philo, time_diff_ms(sim_start, start_eat), EAT);
	philo->time_last_meal = start_eat;
	philo->nbr_meal_eaten += 1;
	pthread_mutex_unlock(&philo->eating);
	time_sleep_ms(philo->public_data->time_eat);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	philo->status = SLEEP;
}

void	go_sleep(t_philo *philo, const int64_t sim_start)
{
	const int64_t	start_sleep = time_of_day_ms();

	philo_queue_message(philo, time_diff_ms(sim_start, start_sleep), SLEEP);
	time_sleep_ms(philo->public_data->time_sleep);
	philo->status = THINK;
}

void	go_think(t_philo *philo, const int64_t sim_start)
{
	const int64_t	start_think = time_of_day_ms();

	philo_queue_message(philo, time_diff_ms(sim_start, start_think), THINK);
	philo->status = EAT;
}
