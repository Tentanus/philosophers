/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_error.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:50:21 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/23 15:58:48 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

const char	*philo_error_message(int code)
{
	const char	*message[] = {
	[ERR_ARG] = "INCORRECT ARGUMENTS: 4 or 5",
	[ERR_INP] = "INCORRECT INPUT: 1 till INT_MAX"
	};

	return (message[code]);
}

int	philo_error(int32_t code)
{
	ph_putstr_fd(STDERR_FILENO, "philo: ");
	ph_putendl_fd(STDERR_FILENO, philo_error_message(code));
	return (code);
}
