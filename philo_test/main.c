/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mweverli <mweverli@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/21 21:12:49 by mweverli      #+#    #+#                 */
/*   Updated: 2022/12/22 15:03:31 by mweverli      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include <pthread.h>
#include <stdio.h>

typedef struct s_arg {
	int		*val;
	char	s[10];
} t_arg;

int		ft_strlen(const char *inp)
{
	int i = 0;

	while (inp[i] != '\0')
		i++;
	return (i);
}

void	write_str(t_arg *arg, const char *inp)
{
	int i = ft_strlen(inp);
	while (i--)
		arg->s[i] = inp[i];
}

void	*increase_val(void *ptr)
{
	t_arg	*arg = (t_arg *) ptr;

	*(arg->val) += 1;
	printf("%s with val: %d\n", arg->s, *(arg->val));
	return (NULL);
}

int main(void)
{
	int			val, t_ret1, t_ret2;
	pthread_t	thread1, thread2;
	t_arg		arg1, arg2;
	thread1 = NULL;
	thread2 = NULL;

	val = 0;
	arg1.val = &val;
	write_str(&arg1, "thread_1");
	arg2.val = &val;
	write_str(&arg2, "thread_2");

	printf("setup complete\n");

	t_ret1 = pthread_create(&thread1, NULL, increase_val, (void *) &arg1);
	printf("t1 startedi\n");
	t_ret2 = pthread_create(&thread2, NULL, increase_val, (void *) &arg2);
	printf("t2 startedi\n");

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return (0);
}
