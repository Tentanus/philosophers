/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:36:12 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/26 21:22:38 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	philo_alloc_fill(t_philo *philos, pthread_mutex_t *forks, size_t nbr)
{
	philos->thread = ph_calloc(sizeof(pthread_t), 1);
	if (!(philos->thread))
		return (ERR_MEM);
	philos->philo_id = nbr;
	philos->nbr_meal_eaten = 0;
	philos->time_last_meal = 0;
	philos->fork_r = &forks[nbr];
	philos->fork_l = &forks[nbr + 1];
	if ((int32_t) nbr == (philos->public_data->nbr_philo - 1))
		philos->fork_l = &forks[0];
	return (SUCCESS);
}

int32_t	philo_alloc(t_public *info, t_philo **philos)
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
		if (philo_alloc_fill(&philos[0][i], forks, i) != SUCCESS)
			return (philo_alloc_free(*philos, forks, i), ERR_MEM);
		i++;
	}
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
	info->death = false;
	return (SUCCESS);
}

