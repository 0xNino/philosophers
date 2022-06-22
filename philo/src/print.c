/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 15:36:53 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/21 16:33:34 by 0xNino           ###   ########.fr       */
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
	if (check_death(info) && (info->satiated_nb < nb_philo && nb_philo != 1))
	{
		time = philo_time() - info->start_time;
		printf("%s  💀\t%li ms     Philo #%d\thas died\n%s", RED,
			time, philo->id + 1, RESET);
		printf("%s%s\n%s", WHITE, DASH, RESET);
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
		printf("%s  💭\t%li ms     Philo #%d\tis thinking\n%s", WHITE,
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
		printf("%s  💤\t%li ms     Philo #%d\tis sleeping\n%s", WHITE,
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

	nb_philo = info->nb_philo;
	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->satiated);
	if (check_death(info) && (info->satiated_nb < nb_philo && nb_philo != 1))
	{
		time = philo_time() - info->start_time;
		printf("%s  🥄\t%li ms     Philo #%d\thas taken the fork #%d\n%s", WHITE,
			time, philo->id + 1, fork + 1, RESET);
		printf("%s%s\n%s", GRAY, DASH, RESET);
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->write);
}

void	print_meal(t_info *info, t_philo *philo, int count)
{
	long	time;

	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->satiated);
	if (check_death(info) && (info->satiated_nb <= info->nb_philo))
	{
		time = philo_time() - info->start_time;
		if (info->nb_meals_req <= 0)
			printf("%s  🍝\t%li ms     Philo #%d\tis eating\t%d\n%s", WHITE,
				time, philo->id + 1, count, RESET);
		else if (count >= info->nb_meals_req)
			printf("%s  🍝\t%li ms     Philo #%d\tis eating\t%d/%d | %d/%d\n%s",
				GREEN, time, philo->id + 1, count,
				info->nb_meals_req, info->satiated_nb, info->nb_philo, RESET);
		else
			printf("%s  🍝\t%li ms     Philo #%d\tis eating\t%d/%d | %d/%d\n%s",
				YELLOW, time, philo->id + 1, count,
				info->nb_meals_req, info->satiated_nb, info->nb_philo, RESET);
		printf("%s%s\n%s", GRAY, DASH, RESET);
		if (info->satiated_nb == info->nb_philo)
			exit(0);
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->write);
}
