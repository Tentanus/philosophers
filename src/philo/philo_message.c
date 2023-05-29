/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_message.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 21:15:26 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/29 16:26:13 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static const char	*g_msg[] = {
[FORK] = "has taken a fork",
[EAT] = "is eating",
[SLEEP] = "is sleeping",
[THINK] = "is thinking",
[DIE] = "died",
[END] = "philos ate enough, ending simulation"
};

#ifdef PRETTY
# define FORMAT_MSG "%10lu ms - %3lu - %s\n"
#else
# define FORMAT_MSG "%lu %lu %s\n"
#endif

int32_t	philo_switch_queue(t_msg_queue *queue)
{
	int32_t	*swap_time;
	int32_t	*swap_philo;
	int32_t	*swap_action;
	int32_t	msg_count;

	pthread_mutex_lock(msg_mutex);
	swap_time = queue->time[0];
	swap_philo = queue->philo[0];
	swap_action = queue->action[0];
	queue->time[0] = queue->time[1];
	queue->philo[0] = queue->philo[1];
	queue->action[0] = queue->action[1];
	queue->time[1] = swap_time;
	queue->philo[1] = swap_philo;
	queue->action[1] = swap_action;
	msg_count = queue->count;
	queue->count = 0;
	pthread_mutex_unlock(msg_mutex);
	return (msg_count);
}

void	philo_print_queue(t_msg_queue *queue)
{
	int32_t	max_count;
	int32_t	i;

	while (1)
	{
		i = 0;
		max_count = philo_switch_queue(queue);
		while (i < max_count)
		{
			printf(FORMAT_MSG, queue->time[0][i], queue->philo[0][i], \
				g_msg[queue->action[0][i]]);
			if (queue->action[0][i] == DIE || queue->action[0][i] == END)
				return ;
			i++;
		}
		time_sleep_ms(250);
	}
}

void	philo_queue_message(t_philo *philo, int64_t time, t_msg msg)
{
	int32_t	count;
	t_queue	queue;

	queue = philo->queue;
	pthread_mutex_lock(msg_mutex);
	count = queue->count;
	(queue->count)++;
	pthread_mutex_unlock(msg_mutex);
	queue->time[1][count] = time;
	queue->philo[1][count] = philo->philo_id;
	queue->action[1][count] = msg;
}
