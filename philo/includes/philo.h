/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:22:17 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/16 09:40:57 by 0xNino           ###   ########.fr       */
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

// check.c
int		check_death(t_info *info);
int		check_enough(t_info *info);

// end.c
int		end_threads(t_info *info);
int		end_mutexes(t_info *info);

// init.c
int		init_info(char **argv, t_info *info);
int		init_philo(t_info *info);
int		init_mutex(t_info *info);

// philo_utils.c
void	philo_print(t_info *info, int id, char *msg, int fork_id);
void	philo_sleep(t_info *info, long time);
void	philo_meal(t_info *info, t_philo *philo);
long	philo_time(void);

// utils.c
int		error(char *errmsg, int errnum);
int		check_args(int argc, char **argv);

#endif
