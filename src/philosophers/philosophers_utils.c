/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 13:43:13 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/21 15:59:03 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int32_t	ph_strlen(const char *inp)
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
	if (!str)
		return(ph_putendl_fd("(null)", fd));
	write(fd, str, ph_strlen(str));
	write(fd, "\n", 1);
}

int32_t	ph_atoi(char *inp)
{
	int		i;
	long	res;

	if (inp[0] == '-' || ph_strlen(inp) > 10)
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
