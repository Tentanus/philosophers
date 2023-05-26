/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_free.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 18:13:27 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/26 21:22:24 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_alloc_free(t_philo *philos, pthread_mutex_t *forks, size_t limit)
{
	size_t	i;

	i = 0;
	free(forks);
	while(i < limit)
	{
		free(philos[i].thread);
		i++;
	}
	free(philos);
}
