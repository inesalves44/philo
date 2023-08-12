/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:22:00 by idias-al          #+#    #+#             */
/*   Updated: 2023/08/12 11:03:26 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief sees if a philo is dead and changes the control variable to one.
 * @param data -> complete struct of philosopher's data
 * @return int -> 0if all are alive, 0 if one is dead
 */
int	is_any_philo_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->death);
		pthread_mutex_lock(&data->philo[i].m_status);
		if (data->philo[i].status == DEATH)
		{
			pthread_mutex_unlock(&data->philo[i].m_status);
			pthread_mutex_unlock(&data->death);
			print_msg(data->philo[i].i, data->philo[i].time
				- data->philo[i].start_time, "died", data->philo);
			pthread_mutex_lock(&data->test);
			data->control = 1;
			pthread_mutex_unlock(&data->test);
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].m_status);
		pthread_mutex_unlock(&data->death);
		i++;
	}
	return (0);
}

/**
 * @brief checks how many times the philos has eaten
 */
int	check_counting_eats(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->philo[i].m_count_eats);
		if (data->philo[i].counting_eats < data->n_eats)
		{
			pthread_mutex_unlock(&data->philo[i].m_count_eats);
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].m_count_eats);
		i++;
	}
	return (0);
}

/**
 * @brief control thread, checks if any philo is dead and counts how many times 
 * they have eaten
 * @param data1 -> complete data struct
 */
void	*checking_philos(void *data1)
{
	t_data	*data;

	data = (t_data *)data1;
	while (1)
	{
		if (is_any_philo_dead(data))
			return (NULL);
		pthread_mutex_lock(&data->death);
		if (data->n_eats != -1 && !check_counting_eats(data))
		{
			data->control = 1;
			pthread_mutex_unlock(&data->death);
			break ;
		}
		pthread_mutex_unlock(&data->death);
	}
	return (NULL);
}
