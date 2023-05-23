/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 13:43:13 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/23 13:54:07 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int32_t	ph_atoi(char *inp)
{
	int		i;
	long	res;

	if (inp == NULL || inp[0] == '-' || \
			ph_strlen(inp) > 10)
		return (-1);
	i = 0;
	res = 0;
	if (inp[0] == '+')
		inp++;
	while (inp[i] >= '0' && inp[i] <= '9')
	{
		res = res * 10 + (inp[i] - '0');
		i++;
	}
	if (inp[i] != '\0' || res > INT_MAX || res < -1)
		return (-1);
	return (res);
}
