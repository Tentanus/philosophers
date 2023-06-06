/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_message.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 21:15:26 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/05 22:14:10 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static const char	*g_msg[] = {
[FORK] = "has taken a fork",
[EAT] = "is eating",
[SLEEP] = "is sleeping",
[THINK] = "is thinking",
[DIE] = "died",
[END] = "philos ate enough, ending simulation"
};

static int32_t	printer_switch_queue(t_msg_queue *queue)
{
	int32_t	*swap_time;
	int32_t	*swap_philo;
	int32_t	*swap_action;
	int32_t	msg_count;

	msg_count = queue->count;
	swap_time = queue->time[0];
	swap_philo = queue->philo[0];
	swap_action = queue->action[0];
	queue->time[0] = queue->time[1];
	queue->philo[0] = queue->philo[1];
	queue->action[0] = queue->action[1];
	queue->time[1] = swap_time;
	queue->philo[1] = swap_philo;
	queue->action[1] = swap_action;
	queue->count = 0;
	return (msg_count);
}

void	*philo_printer(void *ptr)
{
	t_msg_queue	*queue;
	int32_t		max_count;
	int32_t		i;

	queue = ptr;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&queue->msg_mutex);
		max_count = printer_switch_queue(queue);
		pthread_mutex_unlock(&queue->msg_mutex);
		while (i < max_count)
		{
			printf(FORMAT_MSG, queue->time[0][i], queue->philo[0][i], \
				g_msg[queue->action[0][i]]);
			if (queue->action[0][i] == DIE || queue->action[0][i] == END)
				return (NULL);
			i++;
		}
		time_sleep_ms(1);
	}
	return (NULL);
}

void	philo_queue_message(t_philo *philo, int32_t time, t_msg msg)
{
	int32_t		count;

	pthread_mutex_lock(&philo->queue->msg_mutex);
	count = philo->queue->count;
	philo->queue->time[1][count] = time;
	philo->queue->philo[1][count] = philo->philo_id;
	philo->queue->action[1][count] = msg;
	(philo->queue->count)++;
	pthread_mutex_unlock(&philo->queue->msg_mutex);
}
