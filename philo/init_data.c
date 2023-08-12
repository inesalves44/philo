/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:05:38 by idias-al          #+#    #+#             */
/*   Updated: 2023/08/12 10:59:49 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @note This function checks if the argument passed is composed of only digits  
 * @param argument -> a string to test
 * @return -> 0 if the strings has only digits, 1 if not 
 */
int	check_digits(char *argument)
{
	int	i;

	i = 0;
	while (argument[i] != '\0')
	{
		if (!ft_isdigit(argument[i]))
			return (1);
		i++;
	}
	return (0);
}

/** 
 * @note  this function checks if the arguments are ok and gives values to 
 * the data struct
 * @param data -> the struct that keeps the values
 * @param argc -> number of arguments given
 * @param argv -> string of strings with the arguments
 * @return -> returns 0 if everything is good, 1 if not.
 */
int	init_var(t_data *data, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_digits(argv[i]))
			return (1);
		i++;
	}
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eats = ft_atoi(argv[5]);
	else
		data->n_eats = -1;
	data->start_time = get_time();
	data->control = 0;
	data->philo = malloc(data->n_philo * sizeof(t_philo));
	return (0);
}

/**
 * @brief Get the time object with the timeval struct
 * @return unsigned long long -> current time 
 */
unsigned long long	get_time(void)
{
	struct timeval		temp;
	unsigned long long	time;

	gettimeofday(&temp, NULL);
	time = temp.tv_sec * 1000 + temp.tv_usec / 1000;
	return (time);
}

/**
 * @brief Populates the data struct and creates the philo structs
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
		data->philo[i].status = ALIVE;
		data->philo[i].start_time = get_time();
		if (i != data->n_philo - 1 && data->n_philo > 1)
			data->philo[i].f_right = &data->philo[i + 1].f_left;
		else if (i == data->n_philo - 1 && data->n_philo > 1)
			data->philo[i].f_right = &data->philo[0].f_left;
		else if (data->n_philo == 1)
			data->philo->f_right = NULL;
		pthread_mutex_init(&data->philo[i].f_left, NULL);
		pthread_mutex_init(&data->philo[i].m_count_eats, NULL);
		pthread_mutex_init(&data->philo[i].m_status, NULL);
		i++;
	}
}
