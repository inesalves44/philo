/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:51:39 by idias-al          #+#    #+#             */
/*   Updated: 2023/05/31 15:13:04 by idias-al         ###   ########.fr       */
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

typedef	struct s_philo
{
	int				i;
	pthread_mutex_t	f_left;
	pthread_mutex_t	*f_right;
	int				t_die;
	int				t_sleep;
	int				t_eating;
	int				n_eats;
	int				time;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				n_philo;
	int				t_die;
	int				t_sleep;
	int				t_eating;
	int				n_eats;
	int				start_time;
	t_philo			*philo;
	pthread_mutex_t print;
	pthread_mutex_t death;
}					t_data;

int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);

#endif