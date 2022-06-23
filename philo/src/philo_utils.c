/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:50:53 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/21 16:37:47 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_sleep(t_info *info, long time)
{
	long	i;

	i = philo_time();
	while (check_death(info))
	{
		if (philo_time() - i >= time)
			break ;
		usleep(5);
	}
}

void	philo_meal(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->forks[philo->left_fork_id]);
	print_fork(info, philo, philo->left_fork_id);
	pthread_mutex_lock(&info->forks[philo->right_fork_id]);
	print_fork(info, philo, philo->right_fork_id);
	pthread_mutex_lock(&info->time_check);
	philo->last_meal_time = philo_time();
	pthread_mutex_unlock(&info->time_check);
	pthread_mutex_lock(&info->meals_eaten);
	print_meal(info, philo, philo->nb_meals + 1);
	pthread_mutex_unlock(&info->meals_eaten);
	philo_sleep(info, info->time_eat);
	pthread_mutex_lock(&info->meals_eaten);
	philo->nb_meals++;
	pthread_mutex_unlock(&info->meals_eaten);
	pthread_mutex_unlock(&info->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&info->forks[philo->right_fork_id]);
}

long	philo_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	philo_error(char *errmsg, int errnum)
{
	printf("%s", errmsg);
	return (errnum);
}

void	*philo_unlock(pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
	return (SUCCESS);
}
