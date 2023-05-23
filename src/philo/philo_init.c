/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_init.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:36:12 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/23 17:22:58 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	philo_alloc(t_public *info, pthread_t **philo)
{
	info = NULL;
	philo = NULL;
	return (0);
}

int32_t	philo_init(char **argv, t_public *info)
{
	if (!*argv[0] || !*argv[1] || !*argv[2] || !*argv[3] || \
		(argv[4] && !*argv[4]))
		return (1);
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
		return (1);
	info->n_full_philo = 0;
	info->death = false;
	return (0);
}

