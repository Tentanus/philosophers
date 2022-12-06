/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/05 19:56:14 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/06 22:17:25 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	t_philo	info;

	if (argc < 4 || argc > 5)
		philo_error();
	info = philo_init(argv + 1);
	return (printf("succes\n"));
}
