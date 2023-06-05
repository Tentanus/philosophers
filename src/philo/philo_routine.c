/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 17:47:49 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/05 21:51:43 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

typedef void				(*t_go_action) \
							(t_philo *philo, const int64_t sim_start);

static bool	check_err(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->public_data->start);
	ret = philo->public_data->err;
	pthread_mutex_unlock(&philo->public_data->start);
	return (ret);
}

static bool	start_sequence(t_philo *philo, int64_t *sim_start)
{
	bool	err;

	pthread_mutex_lock(&philo->public_data->start);
	*sim_start = philo->public_data->time_start;
	philo->time_last_meal = *sim_start;
	err = philo->public_data->err;
	pthread_mutex_unlock(&philo->public_data->start);
	return (err);
}

static void	check_belly(t_philo *philo)
{
	int32_t	current_meals_ate;
	int32_t	required_meals;

	current_meals_ate = philo->nbr_meal_eaten;
	pthread_mutex_lock(&philo->public_data->start);
	required_meals = philo->public_data->nbr_meal;
	if (current_meals_ate == required_meals)
		(philo->public_data->nbr_full_philo)++;
	pthread_mutex_unlock(&philo->public_data->start);
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

	philo = ptr;
	pthread_mutex_lock(&philo->public_data->start);
	pthread_mutex_unlock(&philo->public_data->start);
	if (start_sequence(philo, &sim_start))
		return (NULL);
	if (philo->philo_id % 2 == 1)
	{
		go_think(philo, sim_start);
		time_sleep_ms(philo->public_data->time_eat / 2);
	}
	while (1)
	{
		if (check_err(philo))
			break ;
		check_belly(philo);
		g_func[philo->status](philo, sim_start);
	}
	return (NULL);
}
