/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:56:14 by mweverli      #+#    #+#                 */
/*   Updated: 2023/04/02 19:46:58 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int philo(t_philo info)
{
	info.n_meal = 3;
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	info;
	int		status;

	if (argc < 5 || argc > 6)
		return (philo_error(ARGUMENTS));
	else if (philo_init(argv + 1, &info))
		return (philo_error(INPUT));
	status = philo(info);
	return (philo_error(status));
}

//	Make my own sleep function. [usleep] doesn't work precisely enough and can cause dataraces
//	Use a mutex lock on my write function so write function won't be used twice 
