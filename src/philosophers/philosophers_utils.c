/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 13:43:13 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/19 13:58:33 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

uint32_t	ph_strlen(char *inp)
{
	int	i;

	if (!inp)
		return (0);
	i = 0;
	while (inp[i])
		i++;
	return (i);
}

void	ph_putendl_fd(const char *str, int fd)
{
	if (!s)
		return(ph_putendl_fd("(null)", fd));
	i = ph_strlen(s);
	write(fd, s, i);
	write(fd, "\n", 1);
}

uint32_t	ph_atoi(char *inp)
{
	int		i;
	long	res;

	if (inp[0] == '-' || ph_strlen(inp) > 10)
		philo_error(INPUT);
	i = 0;
	res = 0;
	if (inp[0] == '+')
		inp++;
	while (inp[i] >= '0' && inp[i] <= '9')
	{
		res = res * 10 + (inp[i] - '0');
		i++;
	}
	if (inp[i] != '\0' || res > UINT_MAX || res < 1)
		philo_error(INPUT);
	return (res);
}
