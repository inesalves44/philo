/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 13:06:43 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/31 10:38:30 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_signal(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	return_s(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	number;
	int	signal;

	i = 0;
	signal = 1;
	number = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (is_signal(nptr[i]) == 1)
	{
		signal = return_s(nptr[i]) * signal;
		i++;
	}
	while (nptr[i] != '\0' && is_number(nptr[i]) == 1)
	{
		number = 10 * number + (nptr[i] - '0');
		i++;
	}
	return (number * signal);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*t_data	*create_node(t_philo philo, int j, t_data *head)
{
	t_data	*test;
	
	test = malloc(sizeof(t_data));
	if (test)
	{
		test->i = j;
		test->time = philo.start_time;
		test->n_eats = philo.n_eats;
		test->t_die = philo.t_die;
		test->t_eating = philo.t_eating;
		test->t_sleep = philo.t_sleep;
		test->next = head;
	}
	return (test);
}

t_data	*create_list(t_philo philo)
{
	int		i;
	int		j;
	t_data	*test;
	t_data	*head;

	i = 0;
	j = 1;
	test = create_node(philo, j, NULL);
	head = test;
	j++;
	i++;
	while (i < philo.n_philo)
	{
		test->next = create_node(philo, j, head);
		test = test->next;
		i++;
		j++;
	}
	return (head);
}*/