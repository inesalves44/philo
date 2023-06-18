/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:45:18 by idias-al          #+#    #+#             */
/*   Updated: 2023/06/18 10:58:38 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	create_philos(t_data data, int i)
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
	return (data);
}