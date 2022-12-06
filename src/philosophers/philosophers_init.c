/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_init.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 19:36:12 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/06 22:17:24 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

uint32_t	ph_strlen(char *inp)
{
	int	i;

	if (!inp)
		return (0);
	i = 0;
	while (inp[i])
		i++;
	return (i);;
}

uint32_t	ph_atoi(char *inp)
{
	int		i;
	long	res;

	if (inp[0] == '-' || ph_strlen(inp) > 10)
		philo_error();
	i = 0;
	res = 0;
	if (inp[0] == '+')
		inp++;
	while (inp[i] >= '0' && inp[i] <= '9')
	{
		res = res * 10 + (inp[i] - '0');
		i++;
	}
	if (inp[i] != '\0' || res > UINT_MAX)
		philo_error();
	return (res);
}

t_philo	philo_init(char **argv)
{
	t_philo	info;

	if (!*argv[0] || !*argv[1] || !*argv[2] || !*argv[3]
			|| (argv[4] && !*argv[4]))
		philo_error();
	info.n_philo = ph_atoi(argv[0]);
	info.t_die = ph_atoi(argv[1]);
	info.t_eat = ph_atoi(argv[2]);
	info.t_sleep = ph_atoi(argv[3]);
	if (argv[4])
		info.n_meal = ph_atoi(argv[4]);
	else
		info.n_meal = 0;
	return (info);
}
