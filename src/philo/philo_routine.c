/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 17:47:49 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/05 19:50:05 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

typedef void				(*t_go_action) \
							(t_philo *philo, const int64_t sim_start);

static bool	check_err(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->eating);
	ret = philo->public_data->err;
	pthread_mutex_unlock(&philo->eating);
	return (ret);
}

static bool	start_sequence(t_philo *philo, int64_t *sim_start)
{
	bool	err;

	pthread_mutex_lock(&philo->eating);
	*sim_start = philo->public_data->time_start;
	philo->time_last_meal = *sim_start;
	err = philo->public_data->err;
	pthread_mutex_unlock(&philo->eating);
	return (err);
}

static const t_go_action	g_func[4] = {
[0] = NULL,
[1] = go_eat,
[2] = go_sleep,
[3] = go_think,
};

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	int64_t	sim_start;
	bool	err;

	philo = ptr;
	pthread_mutex_lock(&philo->public_data->start);
	pthread_mutex_unlock(&philo->public_data->start);
	err = start_sequence(philo, &sim_start);
	if (err == true)
		return (NULL);
	if (philo->philo_id % 2 == 1)
	{
		go_think(philo, sim_start);
		time_sleep_ms(philo->public_data->time_eat / 2);
	}
	while (1)
	{
		err = check_err(philo);
		if (err == true)
			break ;
		g_func[philo->status](philo, sim_start);
	}
	return (NULL);
}
