/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:45:18 by idias-al          #+#    #+#             */
/*   Updated: 2023/07/18 18:12:27 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 * 
 * @param philo 
 */
void	start_philo_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mstart_time);
	if (philo->i == 1)
		philo->data->start_time = get_time();
	pthread_mutex_unlock(&philo->data->mstart_time);
}

/**
 * @brief 
 * 
 * @param philo 
 * @return int 
 */
int	philo_thinking_and_sleeping(t_philo *philo)
{
	if (is_dead(philo))
		return (1);
	pthread_mutex_lock(&philo->m_count_eats);
	philo->counting_eats++;
	pthread_mutex_unlock(&philo->m_count_eats);
	print_msg(philo->i, get_time() - philo->start_time,
		"is sleeping", philo);
	usleep(philo->data->t_sleep * 1000);
	if (is_dead(philo))
		return (1);
	print_msg(philo->i, get_time() - philo->start_time,
		"is thinking", philo);
	return (0);
}

/** 
 * @note -> the function that is called when philo threads are created 
 * @param philo1 -> struct for one philosopher
 * @return -> a void *
 */
void	*philo(void *philo1)
{
	t_philo	*philo;

	philo = (t_philo *)philo1;
	start_philo_time(philo);
	while (1)
	{
		if (get_the_forks(philo))
			break ;
		if (is_dead(philo))
		{
			pthread_mutex_unlock(&philo->f_left);
			pthread_mutex_unlock(philo->f_right);
			break ;
		}
		eat_philo(philo);
		if (philo_thinking_and_sleeping(philo))
			break ;
	}
	return (NULL);
}

/**
 * @brief the function called by the thread when one philo is created.
 * he just picks up a fork and cannot eat
 * @param philo1 -> a struct for a philo
 * @return void* -> null
 */
void	*one_philo(void *philo1)
{
	t_philo	*philo;

	philo = (t_philo *)philo1;
	print_msg(philo->i, get_time() - philo->data->start_time,
		"has taken a fork", philo);
	usleep((philo->data->t_die + 1) * 1000);
	print_msg(philo->i, get_time() - philo->data->start_time, "died", philo);
	return (NULL);
}
