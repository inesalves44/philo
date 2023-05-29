/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:49:53 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/29 19:15:12 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// PENSAR EM COMO AS THREADS CORREM NO INFINITO E PERCEBER COMO USAR O TEMPO

int	isdead(t_philo *philo)
{
	return (1);
}


void	*hello_thread(void	*test1)
{
	t_philo	*philo;
	int i = 0;

	philo = (t_philo *)test1;
	while (i <= 5)
	{
		pthread_mutex_lock(&philo->test[philo->test->i].fork);
		pthread_mutex_lock(&philo->test[philo->test->i + 1].fork);
		pthread_mutex_lock(&philo->print);
		printf("Philosopher %d picked up a fork\n", philo->test->i);
		printf("Philosopher %d is eating\n", philo->test->i);
		pthread_mutex_unlock(&philo->print);
		pthread_mutex_unlock(&philo->test[philo->test->i].fork);
		pthread_mutex_unlock(&philo->test[philo->test->i + 1].fork);
		usleep(philo->test->t_eating / 10);
		philo->test->time += philo->test->t_eating;
		pthread_mutex_lock(&philo->print);
		printf("Philosopher %d went to sleep\n", philo->test->i);
		pthread_mutex_unlock(&philo->print);
		usleep(philo->test->t_sleep / 10);
		philo->test->time += philo->test->t_sleep;
		pthread_mutex_lock(&philo->print);
		printf("Philosopher %d started thinking\n", philo->test->i);
		pthread_mutex_unlock(&philo->print);
		i++;
	}
	
}

void	lets_eat(t_philo philo)
{
	pthread_t	thephilo[philo.n_philo];
	int			i;
	int			time;

	i = 0;
	pthread_mutex_init(&philo.death, NULL);
	pthread_mutex_init(&philo.print, NULL);
	while (i < philo.n_philo)
	{
		philo.test[i].i = i + 1;
		philo.test[i].n_eats = philo.n_eats;
		pthread_mutex_init(&philo.test[i].fork, NULL);
		pthread_create(&(thephilo[i]), NULL, hello_thread, &philo.test[i]);
		i++;
	}
	i = 0;
	while (i < philo.n_philo)
	{
		pthread_join(thephilo[i], NULL);
		pthread_mutex_destroy(&philo.test->fork);
		i++;
	}
	pthread_mutex_destroy(&philo.print);
	pthread_mutex_destroy(&philo.death);
}

int	main(int argc, char *argv[])
{
	t_philo			philo;
	t_data			*test;
	struct timeval	temp;

	if (argc < 5)
	{
		printf("Not enough arguments.\n");
		return (1);
	}
	//antes disto tudo é necessário verificar se os argumentos são validos----> função
	gettimeofday(&temp, NULL);
	philo.start_time = temp.tv_sec * 1000 + temp.tv_usec / 1000;
	philo.n_philo = ft_atoi(argv[1]);
	philo.t_die = ft_atoi(argv[2]);
	philo.t_eating = ft_atoi(argv[3]);
	philo.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo.n_eats = ft_atoi(argv[5]);
	else
		philo.n_eats = -1;
	//aqui falta alocar dinamicamente a memomria para philo. ---> philo.test = malloc(argv[1] * t_data)
	philo.test = malloc(philo.n_philo * sizeof(t_data));
	lets_eat(philo);
	return (0);
}
