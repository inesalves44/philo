/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:15:34 by idias-al          #+#    #+#             */
/*   Updated: 2023/06/19 22:47:39 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** 
 * @note this function start the threads that we need for the philosopher's
 * @param data ->struct that has the data from the arguments
 * @return -> 1 if error, 0 if ok
 */
int	starting_threads(t_data data)
{
	create_philos(&data);
	if (data.n_philo == 1)
	{
		if (thread_one_philo(data))
			return (1);
		
	}
	else if (data.n_philo > 1)
	{
		if (thread_multi_philo(data))
			return(1);
	}
	pthread_mutex_destroy(&data.print);
	pthread_mutex_destroy(&data.death);
	free(data.philo);
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