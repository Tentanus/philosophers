/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:56:14 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/19 13:59:10 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int philo(t_philo info)
{
	info = NULL;
}

int	main(int argc, char **argv)
{
	t_philo	info;

	if (argc < 5 || argc > 6)
		philo_error(ARGUMENTS);
	info = philo_init(argv + 1);
	status = philo(info);
	return (philo_error(status));
}
