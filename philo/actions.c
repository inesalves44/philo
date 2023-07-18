/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:26:51 by idias-al          #+#    #+#             */
/*   Updated: 2023/07/18 18:35:44 by idias-al         ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->death);
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->test);
	if (philo->data->control == 1)
	{
		pthread_mutex_unlock(&philo->data->test);
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	if (philo->data->control != 1)
		printf("%lld %d %s\n", time_stamp, i, msg);
	pthread_mutex_unlock(&philo->data->test);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}

/**
 * @brief this function is to confirm if the other philos are dead
 * @param philo -> philo struct
 * @return int ->1 if any other philo is dead or if the philo has eaten
 */
int	confirm_other_philos(t_philo *philo)
{
	if (philo->counting_eats == philo->data->n_eats)
		return (1);
	pthread_mutex_lock(&philo->data->test);
	if (philo->data->control == 1)
	{
		pthread_mutex_unlock(&philo->data->test);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->test);
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
	if (confirm_other_philos(philo))
	{
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	philo->time = get_time();
	if (philo->time - philo->last_meal > (unsigned long long)philo->data->t_die)
	{
		pthread_mutex_lock(&philo->data->test);
		if (philo->data->control != 1)
		{
			pthread_mutex_unlock(&philo->data->test);
			pthread_mutex_lock(&philo->m_status);
			philo->status = DEATH;
			pthread_mutex_unlock(&philo->m_status);
		}
		else
			pthread_mutex_unlock(&philo->data->test);
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}

/**
 * @brief Get the the forks object
 * 
 * @param philo 
 * @return int 
 */
int	get_the_forks(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	if (philo->i % 2 == 0)
		pthread_mutex_lock(&philo->f_left);
	else
		pthread_mutex_lock(philo->f_right);
	if (is_dead(philo))
	{
		if (philo->i % 2 == 0)
			pthread_mutex_unlock(&philo->f_left);
		else
			pthread_mutex_unlock(philo->f_right);
		return (1);
	}
	print_msg(philo->i, get_time() - philo->start_time,
		"has taken a fork", philo);
	if (philo->i % 2 != 0)
		pthread_mutex_lock(&philo->f_left);
	else
		pthread_mutex_lock(philo->f_right);
	print_msg(philo->i, get_time() - philo->start_time,
		"has taken a fork", philo);
	return (0);
}

/**
 * @brief 
 * 
 * @param philo 
 * @return int 
 */
int	eat_philo(t_philo *philo)
{
	print_msg(philo->i, get_time() - philo->start_time, "is eating", philo);
	philo->last_meal = get_time() + 10;
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->f_left);
	pthread_mutex_unlock(philo->f_right);
	return (0);
}
