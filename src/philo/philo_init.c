/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_init.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:36:12 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/25 17:15:13 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	philo_alloc(t_public *info, t_philo **philos)
{
	size_t			i;
	pthread_mutex_t	*forks;

	philos = ph_calloc(sizeof(t_philo), info->n_philo);
	if (!philos)
		return (ERR_MEM);
	forks = ph_calloc(sizeof(pthread_mutex_t), info->n_philo);

	i = 0;
	while (i < info->n_philo)
	{
		philo_alloc_fill(philos[i],  
	}
	return (SUCCESS);
}

int32_t	philo_init(char **argv, t_public *info)
{
	if (!*argv[0] || !*argv[1] || !*argv[2] || !*argv[3] || \
		(argv[4] && !*argv[4]))
		return (ERR_INP);
	info->n_philo = ph_atoi(argv[0]);
	info->t_die = ph_atoi(argv[1]);
	info->t_eat = ph_atoi(argv[2]);
	info->t_sleep = ph_atoi(argv[3]);
	if (argv[4])
		info->n_meal = ph_atoi(argv[4]);
	else
		info->n_meal = -1;
	if (info->n_philo < 1 || info->t_die < 1 || info->t_eat < 1 || \
		info->t_sleep < 1 || (argv[4] && info->n_meal < 1))
		return (ERR_INP);
	info->n_full_philo = 0;
	info->death = false;
	return (SUCCESS);
}

