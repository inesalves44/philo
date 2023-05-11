/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:49:53 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/11 21:36:32 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// PENSAR EM COMO AS THREADS CORREM NO INFINITO E PERCEBER COMO USAR O TEMPO

void	*hello_thread(void	*test1)
{
	t_data	*test;


	test = (t_data *)test1;
	pthread_mutex_lock(&test->mutex);
	pthread_mutex_lock(&test->next->mutex);
	printf("Philosopher %d picked up a fork\n", test->i);
	printf("Philosopher %d is eating\n", test->i);
	usleep(test->t_eating);
	test->time += test->t_eating;
	printf("Philosopher %d went to sleep\n", test->i);
	pthread_mutex_unlock(&test->mutex);
	pthread_mutex_unlock(&test->next->mutex);
}

void	lets_eat(t_philo philo, t_data *test)
{
	pthread_t	thephilo[philo.n_philo];
	int			i;
	int			time;

	i = 0;
	time = test->time;
	while (i < philo.n_philo)
	{
		pthread_mutex_init(&test->mutex, NULL);
		pthread_create(&(thephilo[i]), NULL, hello_thread, test);
		time = test->time;
		i++;
		test = test->next;
	}
	i = 0;
	while (i < philo.n_philo)
	{
		pthread_join(thephilo[i], NULL);
		pthread_mutex_destroy(&test->mutex);
		i++;
		test = test->next;
	}
}

t_data	*create_node(t_philo philo, int j, t_data *head)
{
	t_data	*test;
	
	test = malloc(sizeof(t_data));
	if (test)
	{
		test->i = j;
		test->time = philo.start_time;
		test->n_eats = philo.n_eats;
		test->t_die = philo.t_die;
		test->t_eating = philo.t_eating;
		test->t_sleep = philo.t_sleep;
		test->next = head;
	}
	return (test);
}

t_data	*create_list(t_philo philo)
{
	int		i;
	int		j;
	t_data	*test;
	t_data	*head;

	i = 0;
	j = 1;
	test = create_node(philo, j, NULL);
	head = test;
	j++;
	i++;
	while (i < philo.n_philo)
	{
		test->next = create_node(philo, j, head);
		test = test->next;
		i++;
		j++;
	}
	return (head);
}

int	main(int argc, char *argv[])
{
	struct timeval	current_time;
	t_philo			philo;
	t_data			*test;

	if (argc < 5)
	{
		printf("Not enough arguments.\n");
		return (1);
	}
	philo.n_philo = ft_atoi(argv[1]);
	philo.t_die = ft_atoi(argv[2]);
	philo.t_eating = ft_atoi(argv[3]);
	philo.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.n_eats = ft_atoi(argv[5]);
	else
		philo.n_eats = -1;
	gettimeofday(&current_time, NULL);   
	philo.start_time = current_time.tv_sec * 1000;
	test = create_list(philo);
	lets_eat(philo, test);
	gettimeofday(&current_time, NULL);
	return (0);
}
