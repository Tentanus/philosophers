/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_utils_mem.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 13:54:53 by mweverli      #+#    #+#                 */
/*   Updated: 2023/06/02 20:06:46 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ph_memset(void *ptr, int c, size_t len)
{
	unsigned char	*b;

	b = ptr;
	while (len > 0)
	{
		*b = c;
		b++;
		len--;
	}
	return (ptr);
}

void	*ph_calloc(size_t byte, size_t size)
{
	void	*ptr;

	ptr = malloc(byte * size);
	if (!ptr)
		return (NULL);
	ph_memset(ptr, 0, byte * size);
	return (ptr);
}
