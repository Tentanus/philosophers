/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:50:21 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/22 15:36:06 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

const char	*philo_error_message(int code)
{
	const char	*message[] = {
		[ARGUMENTS] = "Give 4 or 5 arguments",
		[INPUT] = "Give an unsigned int as input"
	};
	return (message[code]);
}

int	philo_error(int code)
{
	if (!code)
		exit(EXIT_SUCCESS);
	ph_putendl_fd(philo_error_message(code), STDERR_FILENO);
	exit(EXIT_FAILURE);
}
