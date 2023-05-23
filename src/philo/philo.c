/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:56:14 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/23 14:10:54 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_philo(t_public	info)
{
	printf("\t-=-\tPHILO PRINT\t-=-\n");
	printf("\n");
	printf("philos:\t\t%d\n", info.n_philo);
	printf("meals:\t\t%d\n", info.n_meal);
	printf("\n");
	printf("time to:\t[ms]\n");
	printf("eat:\t\t%d\n",info.t_eat);
	printf("sleep:\t\t%d\n",info.t_sleep);
	printf("die:\t\t%d\n",info.t_die);
	printf("\n\t-=-\tEND PRINT\t-=-\n");
}

int	philo_single(t_public info)
{
	printf("%d\t%d\t%s\n", 0, 1, FORK);
	usleep(info.t_die * 1000);
	printf("%d\t%d\t%s\n", info.t_die, 1, DEAD);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_public	info;

	if (argc < 5 || argc > 6)
		return (philo_error(ERR_ARG));
	if (philo_init(argv + 1, &info))
		return (philo_error(ERR_INP));
	print_philo(info);
	if (info.n_philo == 1)
		return (philo_single(info));

	return (SUCCESS);
}

//	Make my own sleep function. [usleep] doesn't work precisely enough and can cause dataraces
//
//	make overviewing thread
//	make sure mutex_locks are removed after a philo dies
//	Use a mutex lock on my write function so write function won't be used twice 
