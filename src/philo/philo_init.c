/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_init.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:36:12 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/22 21:37:47 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	philo_init(char **argv, t_public *info)
{
	if (!*argv[0] || !*argv[1] || !*argv[2] || !*argv[3] || \
		(argv[4] && !*argv[4]))
		return(0);
	info->n_philo = ph_atoi(argv[0]);
	info->t_die = ph_atoi(argv[1]);
	info->t_eat = ph_atoi(argv[2]);
	info->t_sleep = ph_atoi(argv[3]);
	if (argv[4])
		info->n_meal = ph_atoi(argv[4]);
	else
		info->n_meal = 0;
	if (info->n_philo < 1 || \
		info->t_die < 0 || \
		info->t_eat < 0 || \
		info->t_sleep < 0 || \
		info->n_meal < 0)
		return (1);
	if (!argv[4])
		info->n_meal = -1;
	return (1);
}

//	make een eigen sleep functie.
//	mutex lock on write function. 
