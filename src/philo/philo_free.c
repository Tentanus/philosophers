/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_free.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 18:13:27 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/09 15:25:52 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_free_philos(t_philo *philos, pthread_mutex_t *forks, size_t limit)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(&philos[0].public_data->start);
	while (i < limit)
	{
		pthread_mutex_destroy(philos[i].fork_r);
		free(philos[i].thread);
		i++;
	}
	free(forks);
	free(philos);
}

void	philo_free_queue(t_msg_queue *queue)
{
	pthread_mutex_destroy(&queue->msg_mutex);
	if (queue->time[0] != NULL)
		free(queue->time[0]);
	if (queue->time[1] != NULL)
		free(queue->time[1]);
	if (queue->philo[0] != NULL)
		free(queue->philo[0]);
	if (queue->philo[1] != NULL)
		free(queue->philo[1]);
	if (queue->action[0] != NULL)
		free(queue->action[0]);
	if (queue->action[1] != NULL)
		free(queue->action[1]);
	queue->time[0] = NULL;
	queue->time[1] = NULL;
	queue->philo[0] = NULL;
	queue->philo[1] = NULL;
	queue->action[0] = NULL;
	queue->action[1] = NULL;
}

void	philo_thread_join(t_philo *philos, size_t max_philos)
{
	size_t	i;

	i = 0;
	while (i < max_philos)
	{
		pthread_join(*philos[i].thread, NULL);
		i++;
	}
}
