/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:36:53 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/23 02:58:20 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_death(t_info *info, t_philo *philo)
{
	long	time;
	int		nb_philo;

	nb_philo = info->nb_philo;
	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->satiated);
	if (check_death(info) && (info->satiated_nb < nb_philo || nb_philo == 1))
	{
		time = philo_time() - info->start_time;
		pthread_mutex_lock(&info->starvation);
		printf("%s  💀\t%li ms\t   Philo #%d\thas died\t\t\t%li ⏱️\n%s", RED,
			time, philo->id + 1, time - philo->starvation_time, RESET);
		pthread_mutex_unlock(&info->starvation);
		printf("%s%s\n%s", GRAY, DASH, RESET);
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->write);
}

void	print_think(t_info *info, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->satiated);
	if (check_death(info) && (info->satiated_nb < info->nb_philo))
	{
		time = philo_time() - info->start_time;
		printf("%s  💭\t%li ms\t   Philo #%d\tis thinking\n%s", WHITE,
			time, philo->id + 1, RESET);
		printf("%s%s\n%s", GRAY, DASH, RESET);
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->write);
}

void	print_sleep(t_info *info, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->satiated);
	if (check_death(info) && (info->satiated_nb < info->nb_philo))
	{
		time = philo_time() - info->start_time;
		printf("%s  💤\t%li ms\t   Philo #%d\tis sleeping\n%s", WHITE,
			time, philo->id + 1, RESET);
		printf("%s%s\n%s", GRAY, DASH, RESET);
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->write);
}

void	print_fork(t_info *info, t_philo *philo, int fork)
{
	long	time;
	int		nb_philo;

	pthread_mutex_lock(&info->write);
	nb_philo = info->nb_philo;
	pthread_mutex_lock(&info->satiated);
	if (check_death(info) && (info->satiated_nb <= nb_philo || nb_philo == 1))
	{
		time = philo_time() - info->start_time;
		printf("%s  🥄\t%li ms\t   Philo #%d\thas taken the fork #%d\n%s",
			WHITE, time, philo->id + 1, fork + 1, RESET);
		printf("%s%s\n%s", GRAY, DASH, RESET);
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->write);
}

void	print_meal(t_info *info, t_philo *philo, int count)
{
	long	time;
	int		sat_nb;

	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->starvation);
	if (check_death(info))
	{
		time = philo_time() - info->start_time;
		sat_nb = info->satiated_nb;
		if (time <= 401)
			philo->starvation_time = info->time_die;
		print_meals(info, philo, count, time);
		printf("%s%s\n%s", GRAY, DASH, RESET);
		philo->starvation_time = time + info->time_die;
	}
	pthread_mutex_unlock(&info->starvation);
	pthread_mutex_unlock(&info->write);
}
