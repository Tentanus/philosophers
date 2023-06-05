/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_run.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 15:04:01 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/05 19:50:06 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	philo_watcher(t_philo *philos)
{
	t_public	*public;
	size_t		i;
	int32_t		diff;

	public = philos[0].public_data;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&(philos[i].eating));
		diff = time_diff_ms(philos[i].time_last_meal, time_of_day_ms());
		if (diff >= public->time_die)
		{
			philo_queue_message(&philos[i], \
				time_diff_ms(public->time_start, time_of_day_ms()), DIE);
			public->err = true;
			pthread_mutex_unlock(&philos[i].eating);
			break ;
		}
		pthread_mutex_unlock(&philos[i].eating);
		if (i == (size_t) public->nbr_philo - 1)
			i = 0;
		else
			i++;
	}
	return ;
}

static int32_t	philo_thread_create(t_philo *philos, t_public *info, \
		pthread_t *printer)
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
	if (pthread_create(printer, NULL, &philo_printer, philos[0].queue))
	{
		philos[i].public_data->err = true;
		pthread_mutex_unlock(&(info->start));
		philo_thread_join(philos, max_philos);
		return (philo_error(ERR_THR));
	}
	return (SUCCESS);
}

int32_t	philo_run(t_public *info, t_philo *philos)
{
	pthread_t	printer;

	pthread_mutex_lock(&(info->start));
	if (philo_thread_create(philos, info, &printer) == ERR_THR)
		return (ERR_THR);
	info->time_start = time_of_day_ms();
	pthread_mutex_unlock(&(info->start));
	philo_watcher(philos);
	philo_thread_join(philos, info->nbr_philo);
	pthread_join(printer, NULL);
	return (SUCCESS);
}

// the watcher thread should input the DEATH or END message so it happens asap.p
