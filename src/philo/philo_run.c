/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_run.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 15:04:01 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/12 16:45:02 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	check_death(int32_t diff, int32_t time_die, t_philo *philo)
{
	int32_t	start_time;

	if (diff < time_die)
		return (false);
	pthread_mutex_lock(&philo->public_data->start);
	philo->public_data->err = true;
	start_time = philo->public_data->time_start;
	pthread_mutex_unlock(&philo->public_data->start);
	philo_queue_message(philo, \
		time_diff_ms(start_time, time_of_day_ms()), DIE);
	return (true);
}

static bool	check_full_philos(t_philo *philo, t_public *public)
{
	int32_t	full_philos;
	int32_t	nbr_philo;
	int32_t	time_start;

	pthread_mutex_lock(&public->start);
	full_philos = public->nbr_full_philo;
	nbr_philo = public->nbr_philo;
	if (full_philos == nbr_philo)
	{
		public->err = true;
		time_start = public->time_start;
		pthread_mutex_unlock(&public->start);
		philo_queue_message(&philo[nbr_philo - 1], \
				time_diff_ms(time_start, time_of_day_ms()), END);
		return (true);
	}
	pthread_mutex_unlock(&public->start);
	return (false);
}

static void	philo_watcher(t_philo *philos)
{
	t_public			*public;
	size_t				i;
	int32_t				diff_time;
	const int32_t		time_die = philos->public_data->time_die;

	public = philos[0].public_data;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&(philos[i].eating));
		diff_time = time_diff_ms(philos[i].time_last_meal, time_of_day_ms());
		pthread_mutex_unlock(&philos[i].eating);
		if (check_err(public))
			break ;
		if (check_death(diff_time, time_die, &philos[i]))
			break ;
		if (check_full_philos(philos, public))
			break ;
		if (i == (size_t) public->nbr_philo - 1)
			i = -1;
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
			return (philo_thread_join(philos, i), ERR_THR);
		}
		i++;
	}
	if (pthread_create(printer, NULL, &philo_printer, philos[0].queue))
	{
		philos[i].public_data->err = true;
		return (philo_thread_join(philos, max_philos), ERR_THR);
	}
	return (SUCCESS);
}

int32_t	philo_run(t_public *info, t_philo *philos)
{
	pthread_t	printer;

	pthread_mutex_lock(&info->start);
	pthread_mutex_lock(&philos[0].queue->msg_mutex);
	if (philo_thread_create(philos, info, &printer) == ERR_THR)
		return (pthread_mutex_unlock(&(info->start)), ERR_THR);
	info->time_start = time_of_day_ms();
	pthread_mutex_unlock(&philos[0].queue->msg_mutex);
	pthread_mutex_unlock(&(info->start));
	philo_watcher(philos);
	philo_thread_join(philos, info->nbr_philo);
	pthread_join(printer, NULL);
	return (SUCCESS);
}

// the watcher thread should input the DEATH or END message so it happens asap.p
