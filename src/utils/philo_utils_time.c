/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils_time.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 19:10:11 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/29 15:03:15 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int64_t	time of day_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int64_t	time_diff_ms(int64_t start, int64_t end)
{
	return (end - start);
}

void	time_sleep_ms(int64_t sleep_ms)
{
	const int64_t	start = tod_ms();

	while (1)
	{
		if (time_diff_ms(start, tod_ms()) >= sleep_ms)
			return ;
		usleep(500);
	}
}
