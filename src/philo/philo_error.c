/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:50:21 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/29 15:00:39 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static const char	*g_err_msg[] = {
[SUCCESS] = "-",
[ERR_ARG] = "INCORRECT ARGUMENTS: 4 or 5",
[ERR_INP] = "INCORRECT INPUT: 1 till INT_MAX",
[ERR_MEM] = "ALLOCATION ERROR"
};

int	philo_error(int32_t code)
{
	ph_putstr_fd(STDERR_FILENO, "philo: ");
	ph_putendl_fd(STDERR_FILENO, g_err_msg[code]);
	return (code);
}
