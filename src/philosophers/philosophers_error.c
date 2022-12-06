/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:50:21 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/06 20:05:47 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	philo_error(void)
{
	write(2, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}
