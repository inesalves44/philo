/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:49:53 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/07 10:31:52 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*hello_thread(void	*aux)
{
	t_aux		*aux1;

	aux1 = (t_aux *)aux;
	printf("This is the thread: %d\n", aux1->id);
}

void	lets_eat(t_philo philo)
{
	pthread_t	thephilo[philo.n_philo];
	int			i;
	t_aux		aux[philo.n_philo];

	i = 0;
	while (i < philo.n_philo)
	{
		aux[i].id = i;
		i++;
	}
	i = 0;
	while (i < philo.n_philo)
	{
		pthread_create(&(thephilo[i]), NULL, hello_thread, &(aux[i]));
		i++;
	}
	i = 0;
	while (i < philo.n_philo)
	{
		pthread_join(thephilo[i], NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	struct timeval	current_time;
	int				time;
	t_philo			philo;

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
	lets_eat(philo);
	time = current_time.tv_sec * 1000;
	gettimeofday(&current_time, NULL);
	return (0);
}
