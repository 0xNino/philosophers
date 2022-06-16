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

void	print(t_info *info, int philo_id, char *msg)
{
	pthread_mutex_lock(&info->write);
	if (check_death(info))
		printf("%li %d %s\n", ft_time() - info->start_time, philo_id + 1, msg);
	pthread_mutex_unlock(&info->write);
}

void	philo_sleep(t_info *info, long time)
{
	long	i;

	i = ft_time();
	while (check_death(info))
	{
		if (ft_time() - i >= time)
			break ;
		usleep(50);
	}
}

void	philo_meal(t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&info->forks[philo->left_fork_id]);
	print(info, philo->id, "has taken a fork");
	pthread_mutex_lock(&info->forks[philo->right_fork_id]);
	print(info, philo->id, "has taken a fork");
	pthread_mutex_lock(&info->time_check);
	philo->last_meal_time = ft_time();
	pthread_mutex_unlock(&info->time_check);
	print(info, philo->id, "is eating");
	philo_sleep(info, info->time_eat);
	pthread_mutex_unlock(&info->forks[philo->left_fork_id]);
	pthread_mutex_unlock(&info->forks[philo->right_fork_id]);
	pthread_mutex_lock(&info->meals_eaten);
	philo->nb_meals++;
	pthread_mutex_unlock(&info->meals_eaten);
}

int	death_monitor(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (!info->enough)
	{
		while (++i < info->nb_philo && check_death(info))
		{
			printf("HELLO : death = %d\n", info->death);
			pthread_mutex_lock(&info->time_check);
			if ((ft_time() - philo->last_meal_time) > info->time_die)
			{
				print(info, philo->id, "has died");
				pthread_mutex_lock(&info->alive);
				info->death = 1;
				pthread_mutex_unlock(&info->alive);
			}
			pthread_mutex_unlock(&info->time_check);
			usleep(50);
		}
		if (info->death)
			break ;
		check_enough(info);
	}
	return (SUCCESS);
}
