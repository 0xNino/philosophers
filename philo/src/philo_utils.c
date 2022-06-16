/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 08:50:53 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/16 09:44:34 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_print(t_info *info, int id, char *msg, int number)
{
	pthread_mutex_lock(&info->write);
	if (check_death(info))
	{
		if (number >= 0)
			printf("%li\t%d %s #%d\n", philo_time() - info->start_time, id + 1, msg, number);
		else
			printf("%li\t%d %s\n", philo_time() - info->start_time, id + 1, msg);
	}
	pthread_mutex_unlock(&info->write);
}

void	philo_sleep(t_info *info, long time)
{
	long	i;

	i = philo_time();
	while (check_death(info))
	{
		if (philo_time() - i >= time)
			break ;
		usleep(50);
	}
}

void	philo_meal(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->forks[philo->left_fork_id]);
	philo_print(info, philo->id, "has taken the fork", philo->left_fork_id);
	pthread_mutex_lock(&info->forks[philo->right_fork_id]);
	philo_print(info, philo->id, "has taken the fork", philo->right_fork_id);
	pthread_mutex_lock(&info->time_check);
	philo->last_meal_time = philo_time();
	pthread_mutex_unlock(&info->time_check);
	philo_print(info, philo->id, "is eating", philo->nb_meals + 1);
	philo_sleep(info, info->time_eat);
	pthread_mutex_unlock(&info->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&info->forks[philo->right_fork_id]);
	pthread_mutex_lock(&info->meals_eaten);
	philo->nb_meals++;
	pthread_mutex_unlock(&info->meals_eaten);
}

long	philo_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
