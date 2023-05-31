/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 10:15:34 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/31 16:15:30 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @note This function checks if the argument passed is only digits  
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
 * @note  this function checks if the arguments are ok and gives values to data
 * @param data -> the struct that keeps the values
 * @param argc -> number of arguments gives
 * @param argv -> string of strings with the arguments
 * @return -> returns 0 if everything is good, 1 if not.
 */

int	init_var(t_data *data, int argc, char *argv[])
{
	int	i;
	struct timeval	temp;
	
	i = 1;
	while (i < argc)
	{
		if (check_digits(argv[i]))
			return (1);
		i++;
	}
	data->n_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eating = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eats = ft_atoi(argv[5]);
	else
		data->n_eats = -1;
	gettimeofday(&temp, NULL);
	data->start_time = temp.tv_sec * 1000 + temp.tv_usec / 1000;
	return (0);
}

/** 
 * @brief  
 * @note   
 * @param data ->
 * @param argc ->
 * @param argv ->
 * @return 
 */
void	*philo(void *philo1)
{
	t_philo *philo;
	int		i;

	philo = (t_philo *)philo1;
	i = 0;
	//while (i < 5)
	//{
		pthread_mutex_lock(&philo->f_left);
		pthread_mutex_lock(philo->f_right);
		//pthread_mutex_lock(&philo->data->print);
		printf("Pick up fork %d\n", philo->i);
		//pthread_mutex_unlock(&philo->data->print);
		usleep(450000);
		pthread_mutex_unlock(&philo->f_left);
		pthread_mutex_unlock(philo->f_right);
		i++;
	//}
	return ((void *)0);
}

/** 
 * @brief  
 * @note   
 * @param data ->
 * @param argc ->
 * @param argv ->
 * @return 
 */
int	starting_threads(t_data data)
{
	pthread_t	thephilo[data.n_philo];
	int			i;

	i = 0;
	data.philo = malloc(data.n_philo * sizeof(t_philo));
	pthread_mutex_init(&data.death, NULL);
	pthread_mutex_init(&data.print, NULL);
	while (i < data.n_philo)
	{
		data.philo[i].i = i + 1;
		data.philo[i].n_eats = data.n_eats;
		data.philo[i].data = &data;
		if (i > 0)
			data.philo[i].f_right = &data.philo[i - 1].f_left;
		else
			data.philo[i].f_right = &data.philo[data.n_philo - 1].f_left;
		pthread_mutex_init(&data.philo[i].f_left, NULL);
		if (pthread_create(&(thephilo[i]), NULL, philo, &data.philo[i]) < 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data.n_philo)
	{
		pthread_join(thephilo[i], NULL);
		pthread_mutex_destroy(&data.philo->f_left);
		i++;
	}
	pthread_mutex_destroy(&data.print);
	pthread_mutex_destroy(&data.death);
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