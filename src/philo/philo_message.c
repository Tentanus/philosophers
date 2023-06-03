/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_message.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 21:15:26 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/03 18:56:34 by mweverli      ########   odam.nl         */
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

void	philo_printer(t_msg_queue *queue)
{
	int32_t		max_count;
	int32_t		i;

	return ;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&queue->msg_mutex);
		max_count = printer_switch_queue(queue);
		pthread_mutex_unlock(&queue->msg_mutex);
		printf("\t-=- SWAPPED -=-\n");
		while (i < max_count)
		{
			printf(FORMAT_MSG, queue->time[0][i], queue->philo[0][i], \
				g_msg[queue->action[0][i]]);
			if (queue->action[0][i] == DIE || queue->action[0][i] == END)
				return ;
			i++;
		}
		time_sleep_ms(400);
		ph_memset(queue->time[0], 0, sizeof(int32_t) * max_count);
		ph_memset(queue->philo[0], 0, sizeof(int32_t) * max_count);
		ph_memset(queue->action[0], 0, sizeof(int32_t) * max_count);
	}
}
// maybe add following line after the while loop containing the printf:
//		time_sleep_ms(250);// this sleep may need some adjusting/fidling might even be unnecesary

void	philo_queue_message(t_philo *philo, int32_t time, t_msg msg)
{
	int32_t		count;
	t_msg_queue	*queue;

	queue = philo->queue;
	pthread_mutex_lock(&queue->msg_mutex);
	count = queue->count;
	queue->time[1][count] = time;
	queue->philo[1][count] = philo->philo_id;
	queue->action[1][count] = msg;
	(queue->count)++;
	pthread_mutex_unlock(&queue->msg_mutex);
}
