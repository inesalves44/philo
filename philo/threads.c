/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 22:38:33 by idias-al          #+#    #+#             */
/*   Updated: 2023/06/19 23:02:50 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_one_philo(t_data data)
{
	pthread_t	thephilo[data.n_philo];

	if (pthread_create(&(thephilo[0]), NULL, one_philo, &data.philo[0]) < 0)
		return (1);
	pthread_join(thephilo[0], NULL);
	pthread_mutex_destroy(&data.philo[0].f_left);
	return (0);
}

int	thread_multi_philo(t_data data)
{
	pthread_t	thephilo[data.n_philo];
	int			i;

	i = 0;
	while (i < data.n_philo)
	{
		if (pthread_create(&(thephilo[i]), NULL, philo, &data.philo[i]) < 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data.n_philo && data.n_philo > 1)
	{
		pthread_join(thephilo[i], NULL);
		i++;
	}
	i = 0;
	while (i++ < data.n_philo && data.n_philo > 1)
		pthread_mutex_destroy(&data.philo[i].f_left);
	return (0);
}