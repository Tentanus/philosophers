/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:50:21 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/18 16:57:19 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

const char	*philo_error_message(int code)
{
	const char	*message[] = {
		[ARGUMENTS] = "INCORRECT ARGUMENTS: 4 or 5",
		[INPUT] = "INCORRECT INPUT: 0 till INT_MAX"
	};
	return (message[code]);
}

int	philo_error(int32_t code)
{
	if (!code)
		exit(EXIT_SUCCESS);
	ph_putstr_fd(STDERR_FILENO, "philo: ");
	ph_putendl_fd(STDERR_FILENO, philo_error_message(code));
	exit(EXIT_FAILURE);
}
