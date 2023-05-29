/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_run.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 15:04:01 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/29 16:21:16 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	start_philo(t_philo *philos, size_t max_philos)
{
	size_t	i;

	i = 0;
	while (i < max_philos)
	{
		if (pthread_create(philos[i].thread, NULL, &philo_routine, &philos[i]))
			return (ERR_THR); // do i have to join all threads?
		i++;
	}
	return (SUCCESS);
}

int32_t	philo_run(t_public *info, t_philo *philos, t_msg_queue *queue)
{
	(void) queue;
	pthread_mutex_lock(&(info->start));
	if (start_philo(philos, info->nbr_philo) == ERR_THR)
		return (ERR_THR);
	return (SUCCESS);
}
