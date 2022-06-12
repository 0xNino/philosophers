/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:22:17 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/03 13:30:36 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <errno.h>

# define SUCCESS 0
# define FAILURE 1
# define TRUE 0
# define FALSE 1

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	int				left_fork_id;
	int				right_fork_id;
	long			last_meal_time;
	struct s_info	*info;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_info
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_meals_req;
	int				death;
	int				enough;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	alive;
	pthread_mutex_t	write;
	pthread_mutex_t	meals_eaten;
	pthread_mutex_t	time_check;
	t_philo			*philos;
}	t_info;

//utils
int		ft_atoi(const char *str);
long	ft_time(void);

#endif
