/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_run.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 15:04:01 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/30 16:21:17 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int32_t	philo_thread_create(t_philo *philos, t_public *info, \
		pthread_t *watcher)
{
	size_t			i;
	const size_t	max_philos = info->nbr_philo;

	i = 0;
	while (i < max_philos)
	{
		if (pthread_create(philos[i].thread, NULL, &philo_routine, &philos[i]))
		{
			philos[i].public_data->err = true;
			pthread_mutex_unlock(&(info->start));
			philo_thread_join(philos, i);
			return (philo_error(ERR_THR));
		}
		i++;
	}
	if (pthread_create(watcher, NULL, &philo_watcher, philos))
	{
		philos[i].public_data->err = true;
		pthread_mutex_unlock(&(info->start));
		philo_thread_join(philos, max_philos);
		return (philo_error(ERR_THR));
	}
	return (SUCCESS);
}

int32_t	philo_run(t_public *info, t_philo *philos, t_msg_queue *queue)
{
	pthread_t	watcher;

	pthread_mutex_lock(&(info->start));
	if (philo_thread_create(philos, info, &watcher) == ERR_THR)
		return (ERR_THR);

//	time_sleep_ms(10);
	info->time_start = time_of_day_ms();
	pthread_mutex_unlock(&(info->start));
	philo_printer(queue);
	return (SUCCESS);
}

// the watcher thread should input the DEATH or END message so it happens asap.p
