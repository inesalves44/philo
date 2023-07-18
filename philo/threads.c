/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:38:33 by idias-al          #+#    #+#             */
/*   Updated: 2023/07/17 23:46:10 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief function for one philo
 * @param data -> with all the data
 * @return int; 0 if ok, 1 on error
 */
int	thread_one_philo(t_data data)
{
	if (pthread_create(&(data.philo[0].philo_thread), NULL, one_philo,
			&data.philo[0]) < 0)
		return (1);
	pthread_join(data.philo[0].philo_thread, NULL);
	pthread_mutex_destroy(&data.philo[0].f_left);
	return (0);
}

/**
 * @brief this function joins the threads and destroys mutexes
 * @param data -> struct of philo
 * @return int 
 */
int	finish_threads(t_data *data, pthread_t aux)
{
	int	i;

	i = 0;
	while (i < data->n_philo && data->n_philo > 1)
	{
		pthread_join(data->philo[i].philo_thread, NULL);
		i++;
	}
	pthread_join(aux, NULL);
	i = 0;
	while (i++ < data->n_philo && data->n_philo > 1)
	{
		pthread_mutex_destroy(&data->philo[i].f_left);
		pthread_mutex_destroy(&data->philo[i].m_count_eats);
		pthread_mutex_destroy(&data->philo[i].m_status);
	}
	return (0);
}

/**
 * @brief threads for multiple philos (more than one)
 * @param data -> struct with all the data
 * @return int -> 1 on error, 0 if ok
 */
int	thread_multi_philo(t_data *data)
{
	pthread_t	aux;
	int			i;

	i = 0;
	data->start_time = get_time();
	while (i < data->n_philo)
	{
		if (pthread_create(&(data->philo[i].philo_thread),
				NULL, philo, &data->philo[i]) < 0)
			return (1);
		i++;
	}
	if (pthread_create(&aux, NULL, checking_philos, data) < 0)
		return (1);
	finish_threads(data, aux);
	return (0);
}
