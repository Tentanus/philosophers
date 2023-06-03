/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_routine.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 17:47:49 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/03 20:13:28 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

typedef void				(*t_go_action) \
							(t_philo *philo, const int64_t sim_start);

void	go_eat(t_philo *philo, const int64_t sim_start)
{
	int64_t	start_eat;

	pthread_mutex_lock(philo->fork_r);
//	philo_queue_message(philo, time_diff_ms(sim_start, time_of_day_ms()), FORK);
	pthread_mutex_lock(philo->fork_l);
//	philo_queue_message(philo, time_diff_ms(sim_start, time_of_day_ms()), FORK);
//	philo_queue_message(philo, time_diff_ms(sim_start, start_eat), EAT);
	if (philo->public_data->err == true)
	{
		pthread_mutex_unlock(philo->fork_r);
		pthread_mutex_unlock(philo->fork_l);
		pthread_mutex_unlock(&philo->eating);
		return ;
	}
	start_eat = time_of_day_ms();
	printf(FORMAT_MSG, time_diff_ms(sim_start, start_eat), philo->philo_id, "is eating");
	pthread_mutex_lock(&philo->eating);
	philo->time_last_meal = start_eat;
	philo->nbr_meal_eaten += 1;
	time_sleep_ms(philo->public_data->time_eat);// - 			time_diff_ms(start_eat, time_of_day_ms()));
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(&philo->eating);
	philo->status = SLEEP;
}

void	go_sleep(t_philo *philo, const int64_t sim_start)
{
	const int64_t	start_sleep = time_of_day_ms();

//	philo_queue_message(philo, time_diff_ms(sim_start, start_sleep), SLEEP);
	if (philo->public_data->err == true)
		return ;
	printf(FORMAT_MSG, time_diff_ms(sim_start, start_sleep), philo->philo_id, "is sleeping");
	time_sleep_ms(philo->public_data->time_sleep);// - 		time_diff_ms(start_sleep, time_of_day_ms()));
	philo->status = THINK;
}

void	go_think(t_philo *philo, const int64_t sim_start)
{
	const int64_t	start_think = time_of_day_ms();

//	philo_queue_message(philo, time_diff_ms(sim_start, start_think), THINK);
	if (philo->public_data->err == true)
		return ;
	printf(FORMAT_MSG, time_diff_ms(sim_start, start_think), philo->philo_id, "is thinking");
	philo->status = EAT;
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
	sim_start = philo->public_data->time_start;
	philo->time_last_meal = sim_start;
	if (philo->public_data->err == true)
		return (NULL);
	if (philo->philo_id % 2 == 1)
	{
		go_think(philo, sim_start);
		time_sleep_ms(philo->public_data->time_eat / 2);
	}
	while (1)
	{
		if (philo->public_data->err == true)
			break ;
		else if (philo->nbr_meal_eaten == philo->public_data->nbr_meal)
		{
			philo->public_data->nbr_full_philo += 1;
			if (philo->public_data->nbr_full_philo != philo->public_data->nbr_philo)
				go_think(philo, sim_start);
			else
				printf("\n%d %d philos full, ending sim\n", time_diff_ms(sim_start, time_of_day_ms()), philo->public_data->nbr_philo);
			break ;
		}
		g_func[philo->status](philo, sim_start);
	}
//	printf("philo [%d] terminated at %d\n", philo->philo_id, time_diff_ms(sim_start, time_of_day_ms()));
	return (NULL);
}
