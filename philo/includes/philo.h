/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:22:17 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/23 02:21:18 by 0xNino           ###   ########.fr       */
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

# define RESET "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[0;97m\002"
# define BLUEBG "\033[48;5;21m"

# define EAT1 "%s  🍝\t%li ms\t   Philo #%d\tis eating\t%d 🍝\t%li ⏱️\n%s"
# define EAT2 "%s  🍝\t%li ms\t   Philo #%d\tis eating  %d/%d 🍝 | %d/%d 😋\t%li ⏱️\n%s"
# define DASH "----------------------------------------------------------------"
# define DASH2 "-------"

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	int				left_fork_id;
	int				right_fork_id;
	long			last_meal_time;
	long			starvation_time;
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
	int				satiated_nb;
	long			start_time;
	pthread_t		satiated_id;
	pthread_mutex_t	*forks;
	pthread_mutex_t	alive;
	pthread_mutex_t	write;
	pthread_mutex_t	meals_eaten;
	pthread_mutex_t	time_check;
	pthread_mutex_t	satiated;
	pthread_mutex_t	starvation;
	t_philo			*philos;
}	t_info;

// check.c
int		check_args(int argc, char **argv);
int		check_death(t_info *info);
int		check_enough(t_info *info);
void	*check_satiated(t_info *info, t_philo *philo);

// end.c
int		end_monitor(t_info *info, t_philo *philo);
int		end_threads(t_info *info);
int		end_mutexes(t_info *info);

// init.c
int		init_info(char **argv, t_info *info);
int		init_philo(t_info *info);
int		init_mutex(t_info *info);

// philo_utils.c
void	philo_sleep(t_info *info, long time);
void	philo_meal(t_info *info, t_philo *philo);
long	philo_time(void);
int		philo_error(char *errmsg, int errnum);
void	*philo_unlock(pthread_mutex_t *mutex);

// print.c
void	print_death(t_info *info, t_philo *philo);
void	print_think(t_info *info, t_philo *philo);
void	print_sleep(t_info *info, t_philo *philo);
void	print_fork(t_info *info, t_philo *philo, int fork);
void	print_meal(t_info *info, t_philo *philo, int count);

// utils.c
int		ft_min(int a, int b);
int		ft_max(int a, int b);

#endif
