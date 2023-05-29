/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_run.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 15:04:01 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/29 17:06:42 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	philo_thread_create(t_philo *philos, size_t max_philos)
{
	size_t	i;

	i = 0;
	while (i < max_philos)
	{
		if (pthread_create(philos[i].thread, NULL, &philo_routine, &philos[i]))
		{
			philos[i].info->err = true;
			pthread_mutex_unlock(&(info->start));
			philo_join_threads(philos, i);
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
	if (philo_thread_create(philos, info->nbr_philo) == ERR_THR)
		return (ERR_THR);
	return (SUCCESS);
}
