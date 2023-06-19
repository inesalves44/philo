/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idias-al <idias-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 21:51:39 by idias-al          #+#    #+#             */
/*   Updated: 2023/06/19 22:51:35 by idias-al         ###   ########.fr       */
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
	int								i;
	pthread_mutex_t					f_left;
	pthread_mutex_t					*f_right;
	int								counting_eats;
	unsigned long long				last_meal;
	unsigned long long				time;
	struct s_data					*data;
}					t_philo;

typedef struct s_data
{
	int								n_philo;
	int								t_die;
	int								t_sleep;
	int								t_eat;
	int								n_eats;
	unsigned long long				start_time;
	t_philo							*philo;
	int								control;
	pthread_mutex_t 				print;
	pthread_mutex_t 				death;
}					t_data;

/*philo.c*/
void	*philo(void *philo1);
void	create_philos(t_data *data);
void	*one_philo(void *philo1);

/*ft_atoi.c*/
int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);

/*init_var.c*/
int				init_var(t_data *data, int argc, char *argv[]);
int				check_digits(char *argument);
unsigned long long	get_time(void);

/*actions.c*/
int	is_dead(t_philo *philo);
int	print_msg(int i, long long unsigned time_stamp, char *msg, t_philo *philo);

/*threads.c*/
int	thread_one_philo(t_data data);
int	thread_multi_philo(t_data data);

#endif