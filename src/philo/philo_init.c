/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:36:12 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/29 17:01:54 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int32_t	philo_alloc_queue(t_msg_queue *queue, int32_t nbr_philo)
{
	ph_memset(queue, 0, sizeof(t_msg_queue));
	queue->time[0] = ph_calloc(sizeof(int32_t), nbr_philo);
	queue->time[1] = ph_calloc(sizeof(int32_t), nbr_philo);
	queue->philo[0] = ph_calloc(sizeof(int32_t), nbr_philo);
	queue->philo[1] = ph_calloc(sizeof(int32_t), nbr_philo);
	queue->action[0] = ph_calloc(sizeof(int32_t), nbr_philo);
	queue->action[1] = ph_calloc(sizeof(int32_t), nbr_philo);
	if (queue->time[0] == NULL || \
		queue->time[1] == NULL || \
		queue->philo[0] == NULL || \
		queue->philo[1] == NULL || \
		queue->action[0] == NULL || \
		queue->action[1] == NULL)
		return (philo_free_queue(queue), ERR_MEM);
	return (SUCCESS);
}

static int32_t	philo_alloc_fill(t_philo *philos, pthread_mutex_t *forks, \
		t_msg_queue *queue, size_t nbr)
{
	philos->thread = ph_calloc(sizeof(pthread_t), 1);
	if (!(philos->thread))
		return (ERR_MEM);
	philos->philo_id = nbr;
	philos->nbr_meal_eaten = 0;
	philos->time_last_meal = 0;
	philos->fork_r = &forks[nbr];
	pthread_mutex_init(&forks[nbr], NULL);
	philos->fork_l = &forks[nbr + 1];
	if ((int32_t) nbr == (philos->public_data->nbr_philo - 1))
		philos->fork_l = &forks[0];
	philos->queue = queue;
	return (SUCCESS);
}

int32_t	philo_alloc(t_public *info, t_philo **philos, t_msg_queue *queue)
{
	size_t			i;
	const size_t	limit = (size_t) info->nbr_philo;
	pthread_mutex_t	*forks;

	*philos = ph_calloc(sizeof(t_philo), info->nbr_philo);
	if (!philos)
		return (ERR_MEM);
	forks = ph_calloc(sizeof(pthread_mutex_t), info->nbr_philo);
	if (!forks)
		return (free(*philos), ERR_MEM);
	i = 0;
	while (i < limit)
	{
		philos[0][i].public_data = info;
		if (philo_alloc_fill(&philos[0][i], forks, queue, i) != SUCCESS)
			return (philo_free_alloc(*philos, forks, i), ERR_MEM);
		i++;
	}
	if (philo_alloc_queue(queue, info->nbr_philo) != SUCCESS)
		return (philo_free_alloc(*philos, forks, i), ERR_MEM);
	return (SUCCESS);
}

int32_t	philo_init(char **argv, t_public *info)
{
	if (!*argv[0] || !*argv[1] || !*argv[2] || !*argv[3] || \
		(argv[4] && !*argv[4]))
		return (ERR_INP);
	info->nbr_philo = ph_atoi(argv[0]);
	info->time_die = ph_atoi(argv[1]);
	info->time_eat = ph_atoi(argv[2]);
	info->time_sleep = ph_atoi(argv[3]);
	if (argv[4])
		info->nbr_meal = ph_atoi(argv[4]);
	else
		info->nbr_meal = -1;
	if (info->nbr_philo < 1 || info->time_die < 1 || info->time_eat < 1 || \
		info->time_sleep < 1 || (argv[4] && info->nbr_meal < 1))
		return (ERR_INP);
	info->nbr_full_philo = 0;
	info->err = false;
	pthread_mutex_init(&(info->start), NULL);
	return (SUCCESS);
}
