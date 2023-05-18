/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:56:14 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/18 16:09:55 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int argc, char **argv)
{
	t_public	info;

	if (argc < 5 || argc > 6)
		return (philo_error(ARGUMENTS));
	philo_init(argv + 1, &info);
	return (SUCCESS);
}

//	Make my own sleep function. [usleep] doesn't work precisely enough and can cause dataraces
//
//	make overviewing thread
//	make sure mutex_locks are removed after a philo dies
//	Use a mutex lock on my write function so write function won't be used twice 
