/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:56:14 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/05 16:39:02 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int	philo_single(t_public info)
{
	printf(FORMAT_MSG, 0, 1, "has taken a fork");
	time_sleep_ms(info.time_die);
	printf(FORMAT_MSG, info.time_die, 1, "died");
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_public	info;
	t_philo		*philos;
	t_msg_queue	queue;

	philos = NULL;
	if (argc < 5 || argc > 6)
		return (philo_error(ERR_ARG));
	if (philo_init(argv + 1, &info))
		return (philo_error(ERR_INP));
	if (info.nbr_philo == 1)
		return (philo_single(info));
	if (philo_alloc(&info, &philos, &queue) != SUCCESS)
		return (philo_error(ERR_MEM));
	if (philo_run(&info, philos) != SUCCESS)
		return (philo_error(ERR_THR));
	philo_free_queue(&queue);
	return (SUCCESS);
}

//
//	make sure mutex_locks are removed after a philo dies
