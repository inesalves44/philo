/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:45:18 by idias-al          #+#    #+#             */
/*   Updated: 2023/06/19 23:27:23 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Create a philos object
 * @param data -> the complete struct for philo
 */
void	create_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(data->n_philo * sizeof(t_philo));
	while (i < data->n_philo)
	{
		data->philo[i].i = i + 1;
		data->philo[i].counting_eats = 0;
		data->philo[i].data = data;
		data->philo[i].last_meal = data->start_time;	
		if (i != data->n_philo - 1 && data->n_philo > 1)
			data->philo[i].f_right = &data->philo[i + 1].f_left;
		else if (i == data->n_philo - 1 && data->n_philo > 1)
			data->philo[i].f_right = &data->philo[0].f_left;
		else if (data->n_philo == 1)
			data->philo->f_right = NULL;
		pthread_mutex_init(&data->philo[i].f_left, NULL);
		i++;
	}
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->print, NULL);
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
	if (philo->i % 2 != 0)
		usleep(1000);
	while (!is_dead(philo))
	{
		if (philo->i % 2 == 0)
			pthread_mutex_lock(&philo->f_left);
		else
			pthread_mutex_lock(philo->f_right);

		if(is_dead(philo))
		{
			if (philo->i % 2 == 0)
				pthread_mutex_unlock(&philo->f_left);
			else
				pthread_mutex_unlock(philo->f_right);
			break;
		}

		print_msg(philo->i, get_time() - philo->data->start_time, "has taken a fork", philo);

		if (philo->i % 2 != 0)
			pthread_mutex_lock(&philo->f_left);
		else
			pthread_mutex_lock(philo->f_right);
	
		if(is_dead(philo))
		{
			pthread_mutex_unlock(&philo->f_left);
			pthread_mutex_unlock(philo->f_right);
			break;
		}

		print_msg(philo->i, get_time() - philo->data->start_time, "has taken a fork", philo);

		//deixa-lo comer
		if(is_dead(philo))
		{
			pthread_mutex_unlock(&philo->f_left);
			pthread_mutex_unlock(philo->f_right);
			break;
		}
		
		print_msg(philo->i, get_time() - philo->data->start_time, "is eating", philo);
		
		//dá o tempo da ultima comida
		philo->last_meal = get_time();
		
		//esta a comer e depois acaba de comer
		usleep(philo->data->t_eat * 1000);
	
		//unlock the forks
		pthread_mutex_unlock(&philo->f_left);

		pthread_mutex_unlock(philo->f_right);
		
		//vai dormir por x tempo
		if(is_dead(philo))
			break;
		
		print_msg(philo->i, get_time() - philo->data->start_time, "is sleeping",philo);
		usleep(philo->data->t_sleep * 1000);

		//vamos pensar
		if(is_dead(philo))
			break;
		print_msg(philo->i, get_time() - philo->data->start_time, "is thinking", philo);
		philo->counting_eats++;
	}
	return (NULL);
}

/**
 * @brief the function calle dby the thread when one philo is created.
 * he just picks yup a fork and cannot eat
 * @param philo1 -> a struct for a philo
 * @return void* -> null
 */
void	*one_philo(void *philo1)
{
	t_philo	*philo;

	philo = (t_philo *)philo1;
	print_msg(philo->i, get_time() - philo->data->start_time, "has taken a fork", philo);
	usleep((philo->data->t_die + 1) * 1000);
	print_msg(philo->i, get_time() - philo->data->start_time, "died", philo);
	return (NULL);
}
