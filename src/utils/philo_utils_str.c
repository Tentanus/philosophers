/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/19 13:43:13 by mweverli      #+#    #+#                 */
/*   Updated: 2023/05/23 13:54:17 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

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

void	ph_putstr_fd(const int fd, const char *str)
{
	if (!str)
		return (ph_putstr_fd(fd, "(null)"));
	write(fd, str, ph_strlen(str));

}
void	ph_putendl_fd(const int fd, const char *str)
{
	ph_putstr_fd(fd, str);
	write(fd, "\n", 1);
}
