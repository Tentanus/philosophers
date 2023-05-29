/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:56:14 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/29 15:57:45 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	philo_print(t_philo *philos, t_public info)
{
	int32_t	i;

	printf("\t-=-\tPHILO PRINT\t-=-\n\n");
	printf("|   INFO:\n");
	printf("|number of philos:\t%d\n", info.nbr_philo);
	printf("|full philos:\t\t%d\n", info.nbr_full_philo);
	printf("|number of meals:\t%d\n", info.nbr_meal);
	printf("|time to die:\t\t%d\n", info.time_die);
	printf("|time to eat:\t\t%d\n", info.time_eat);
	printf("|time to sleep:\t\t%d\n", info.time_sleep);
	printf("|__________________________\n\n");
	i = 0;
	while (i < info.nbr_philo)
	{
		printf("|\tPHILO [%d]\n", philos[i].philo_id);
		printf("|meals had:\t%d\n", philos[i].nbr_meal_eaten);
		printf("|time last:\t%lu\n", philos[i].time_last_meal);
		printf("|fork R:\t%p\n", philos[i].fork_r);
		printf("|fork L:\t%p\n", philos[i].fork_l);
		printf("|info address:\t%p\n", philos[i].public_data);
		printf("|__________________________\n\n");
		i++;
	}
	printf("\n\t-=-\tEND PRINT\t-=-\n");
}

static int	philo_single(t_public info)
{
	printf("%d %d has taken a fork\n", 0, 1);
	usleep(info.time_die * 1000);
	printf("%d %d died\n", info.time_die, 1);
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
	if (philo_run(&info, philos, &queue) != SUCCESS)
		return (philo_error(ERR_THR));
	philo_print(philos, info); // this line needs removal when finished
	return (SUCCESS);
}

//	Make my own sleep function. [usleep] doesn't work precisely enough and can cause dataraces
//
//	make overviewing thread
//	make sure mutex_locks are removed after a philo dies
//	Use a mutex lock on my write function so write function won't be used twice 
