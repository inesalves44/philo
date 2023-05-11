/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:51:39 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/11 20:19:15 by idias-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef	struct s_data
{
	int				i;
	pthread_mutex_t	mutex;
	int	t_die;
	int	t_sleep;
	int	t_eating;
	int	n_eats;
	int	time;
	struct s_data *next;
}	t_data;

typedef struct s_philo
{
	int	n_philo;
	int	t_die;
	int	t_sleep;
	int	t_eating;
	int	n_eats;
	int	start_time;
}		t_philo;

typedef struct	aux
{
	int	id;
}	t_aux;

int	ft_atoi(const char *nptr);

#endif