/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:26:51 by idias-al          #+#    #+#             */
/*   Updated: 2023/06/19 23:41:09 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief This function locks the printf function and then prints the message
 * @param i -> number of philos
 * @param time_stamp -> the current time of the program
 * @param msg -> the message that gives the state of the philo
 * @param philo -> the place where we have the mutex print
 */
int	print_msg(int i, long long unsigned time_stamp, char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->control == 1)
	{
		pthread_mutex_unlock(&philo->data->print);
		return (1);
	}
	printf("%lld %d %s\n", time_stamp, i, msg);
	pthread_mutex_unlock(&philo->data->print);
	return (0);
}

/**
 * @brief  -> checks if a philo is dead, checking the number of meals, 
 * if any other philo is dead and if time has passed
 * @param philo -> a struct for one philo 
 * @return int -> return 1 if dead or 0 if ok
 */
int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->counting_eats == philo->data->n_eats)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	else if (philo->data->control == 1)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	philo->time = get_time();
	if (philo->time - philo->last_meal > (unsigned long long)philo->data->t_die)
	{
		if (philo->data->control != 1)
		{
			print_msg(philo->i, philo->time - philo->data->start_time, "died", philo);
			philo->data->control = 1;
		}
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}