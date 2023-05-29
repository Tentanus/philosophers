/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_run.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 15:04:01 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/29 18:51:50 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int32_t	philo_thread_create(t_philo *philos, t_public *info)
{
	size_t	i;
	const size_t max_philos = info->nbr_philo;

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
	return (SUCCESS);
}

int32_t	philo_run(t_public *info, t_philo *philos, t_msg_queue *queue)
{
	(void) queue;
	pthread_mutex_lock(&(info->start));
	if (philo_thread_create(philos, info) == ERR_THR)
		return (ERR_THR);

	info->time_start = time_of_day_ms();
	pthread_mutex_unlock(&(info->start));
	return (SUCCESS);
}
