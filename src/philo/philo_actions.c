/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_actions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/05 19:35:37 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/06 13:31:05 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	check_belly(t_philo *philo)
{
	int32_t	current_meals_ate;
	int32_t	required_meals;

	current_meals_ate = philo->nbr_meal_eaten;
	pthread_mutex_lock(&philo->public_data->start);
	required_meals = philo->public_data->nbr_meal;
	if (current_meals_ate == required_meals)
		philo->public_data->nbr_full_philo += 1;
	pthread_mutex_unlock(&philo->public_data->start);
}

void	go_eat(t_philo *philo, const int64_t sim_start)
{
	int64_t	start_eat;
	int64_t	time_eat;

	pthread_mutex_lock(&philo->public_data->start);
	time_eat = philo->public_data->time_eat;
	pthread_mutex_unlock(&philo->public_data->start);
	pthread_mutex_lock(philo->fork_r);
	philo_queue_message(philo, time_diff_ms(sim_start, time_of_day_ms()), FORK);
	pthread_mutex_lock(philo->fork_l);
	philo_queue_message(philo, time_diff_ms(sim_start, time_of_day_ms()), FORK);
	start_eat = time_of_day_ms();
	philo_queue_message(philo, time_diff_ms(sim_start, start_eat), EAT);
	pthread_mutex_lock(&philo->eating);
	philo->time_last_meal = start_eat;
	pthread_mutex_unlock(&philo->eating);
	time_sleep_ms(time_eat);
	philo->nbr_meal_eaten += 1;
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	philo->status = SLEEP;
	check_belly(philo);
}

void	go_sleep(t_philo *philo, const int64_t sim_start)
{
	const int64_t	start_sleep = time_of_day_ms();
	int64_t			time_sleep;

	pthread_mutex_lock(&philo->public_data->start);
	time_sleep = philo->public_data->time_sleep;
	pthread_mutex_unlock(&philo->public_data->start);
	philo_queue_message(philo, time_diff_ms(sim_start, start_sleep), SLEEP);
	time_sleep_ms(time_sleep);
	philo->status = THINK;
}

void	go_think(t_philo *philo, const int64_t sim_start)
{
	const int64_t	start_think = time_of_day_ms();

	philo_queue_message(philo, time_diff_ms(sim_start, start_think), THINK);
	philo->status = EAT;
}
