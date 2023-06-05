/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:15:34 by idias-al          #+#    #+#             */
/*   Updated: 2023/06/05 20:13:11 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 * 
 * @param philo 
 * @return int 
 */
int	is_dead(t_philo *philo)
{
	int		time;

	if (philo->n_eats != -1 && philo->counting_eats == philo->n_eats)
		return (1);
	time = get_time();
	if (time - philo->t_eating > philo->data->t_die)
	{
		printf("\n%d IS DEAD\n", philo->i);
		return (1);
	}
	return (0);
}

/** 
 * @note -> the function that is called when threads are created 
 * @param philo1 -> struct for one philosopher
 * @return -> a void *
 */
void	*philo(void *philo1)
{
	t_philo *philo;

	philo = (t_philo *)philo1;
	while (!is_dead(philo))
	{
		//lock garfos
		pthread_mutex_lock(&philo->f_left);
		pthread_mutex_lock(philo->f_right);
		
		//deixa-lo comer
		pthread_mutex_lock(&philo->data->print);
		printf("%d picked up the forks\n", philo->i);
		printf("%d started eating\n", philo->i);
		pthread_mutex_unlock(&philo->data->print);
		
		//esta a comer e depois acaba de comer
		usleep(philo->data->t_eating * 1000);
		pthread_mutex_unlock(&philo->f_left);
		pthread_mutex_unlock(philo->f_right);

		//dá o tempo da ultima comida
		philo->t_eating = get_time();
		
		//vai dormir por x tempo
		pthread_mutex_lock(&philo->data->print);
		printf("%d went to sleep\n", philo->i);
		pthread_mutex_unlock(&philo->data->print);
		usleep(philo->data->t_sleep * 1000);

		//vamos pensar
		pthread_mutex_lock(&philo->data->print);
		printf("%d is thinking\n", philo->i);
		pthread_mutex_unlock(&philo->data->print);
		philo->counting_eats++;
	}
	return ((void *)0);
}

/** 
 * @note this function start the threads that we need for the philosopher's
 * @param data ->struct that has the data from the arguments
 * @return -> 1 if error, 0 if ok
 */
int	starting_threads(t_data data)
{
	pthread_t	thephilo[data.n_philo];
	int			i;

	i = 0;
	data.philo = malloc(data.n_philo * sizeof(t_philo));
	pthread_mutex_init(&data.death, NULL);
	pthread_mutex_init(&data.print, NULL);
	while (i < data.n_philo)
	{
		data.philo[i].i = i + 1;
		data.philo[i].n_eats = data.n_eats;
		data.philo[i].counting_eats = 0;
		data.philo[i].data = &data;
		data.philo[i].t_eating = data.t_eating;
		if (i != data.n_philo - 1)
			data.philo[i].f_right = &data.philo[i + 1].f_left;
		else
			data.philo[i].f_right = &data.philo[0].f_left;
		pthread_mutex_init(&data.philo[i].f_left, NULL);
		if (pthread_create(&(thephilo[i]), NULL, philo, &data.philo[i]) < 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(thephilo[i], NULL);
		pthread_mutex_destroy(&data.philo->f_left);
		i++;
	}
	pthread_mutex_destroy(&data.print);
	pthread_mutex_destroy(&data.death);
	return (0);
}
 

int main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5)
	{
		printf("Not enough arguments.\n");
		return (1);
	}
	if (init_var(&data, argc, argv))
	{
		printf("Error in the arguments.\n");
		return (1);
	}
	if (starting_threads(data) < 0)
	{
		printf("Threads error!\n");
		return (1);
	}
	return (0);	
}