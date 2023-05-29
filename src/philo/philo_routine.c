/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 17:47:49 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/29 19:23:18 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	pthread_mutex_lock(&philo->public_data->start);
	pthread_mutex_unlock(&philo->public_data->start);
	philo->time_last_meal = time_of_day_ms();
	if (philo->public_data->err == true)
		return (NULL);
	return (ptr);
}
