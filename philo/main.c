/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:15:34 by idias-al          #+#    #+#             */
/*   Updated: 2023/06/17 13:58:02 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief This function locks the printf function and then prints the message
 * @param i -> number of philos
 * @param time_stamp -> the current time of the program
 * @param msg -> the message that gives the state of the philo
 * @param data -> the place where we have the mutex print
 */
void	print_msg(int i, long long int time_stamp, char *msg, t_data *data)
{
	pthread_mutex_lock(&data->print);
	printf("%lld %d %s\n", time_stamp, i, msg);
	pthread_mutex_unlock(&data->print);
}

/**
 * @brief 
 * 
 * @param philo 
 * @return int 
 */
int	is_dead(t_philo *philo)
{
	long long int		time;

	if (philo->counting_eats == philo->n_eats)
		return (1);
	time = get_time();
	printf("%lld value of time for %i\n", time - philo->t_eating, philo->i);
	printf("%d", philo->data->t_die);
	if (time - philo->t_eating > philo->data->t_die)
	{
		print_msg(philo->i, get_time() - philo->data->start_time, "has died", philo->data);
		return (1);
	}
	return (0);
}

/** 
 * @note -> the function that is called when philo threads are created 
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
		if (philo->i % 2 == 0)
			pthread_mutex_lock(&philo->f_left);
		else
			pthread_mutex_lock(philo->f_right);
		print_msg(philo->i, get_time() - philo->data->start_time, "has taken a fork", philo->data);
		if (philo->i % 2 == 0)
			pthread_mutex_lock(philo->f_right);
		else
			pthread_mutex_lock(&philo->f_left);
		print_msg(philo->i, get_time() - philo->data->start_time, "has taken a fork", philo->data);

		if (is_dead(philo))
			break;		
		//deixa-lo comer
		print_msg(philo->i, get_time() - philo->data->start_time, "is eating", philo->data);

		//esta a comer e depois acaba de comer
		usleep(philo->data->t_eating * 1000);
		
				
		//dá o tempo da ultima comida
		philo->t_eating = get_time();
		
		//unlock the forks
		if (philo->i %2 == 0)
			pthread_mutex_unlock(&philo->f_left);
		else
			pthread_mutex_unlock(philo->f_right);

		if (philo->i %2 == 0)
			pthread_mutex_unlock(philo->f_right);
		else
			pthread_mutex_unlock(&philo->f_left);
		
		//vai dormir por x tempo
		print_msg(philo->i, get_time() - philo->data->start_time, "is sleeping",philo->data);
		usleep(philo->data->t_sleep * 1000);

		//vamos pensar
		print_msg(philo->i, get_time() - philo->data->start_time, "is thinking",philo->data);

		philo->counting_eats++;
	}
	return ((void *)0);
}

void	*control_thread(void * data1)
{
	t_data *data;

	data = (t_data *) data1;
	while (1)
	{
		
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
	pthread_t	aux;
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
		data.philo[i].t_eating = data.start_time;
		if (i != data.n_philo - 1)
			data.philo[i].f_right = &data.philo[i + 1].f_left;
		else
			data.philo[i].f_right = &data.philo[0].f_left;
		pthread_mutex_init(&data.philo[i].f_left, NULL);
		if (pthread_create(&(thephilo[i]), NULL, philo, &data.philo[i]) < 0)
			return (1);
		i++;
	}
	pthread_create(&aux, NULL, control_thread, &data);
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(thephilo[i], NULL);
		pthread_mutex_destroy(&data.philo[i].f_left);
		if (data.n_philo == 1)
			pthread_mutex_destroy(data.philo[0].f_right);
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