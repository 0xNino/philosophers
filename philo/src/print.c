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
	long	ms;

	nb_philo = info->nb_philo;
	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->satiated);
	if (check_end(info) && (info->satiated_nb < nb_philo || nb_philo == 1))
	{
		time = philo_time() - info->start_time;
		pthread_mutex_lock(&info->starvation);
		ms = philo_time() - philo->last_meal_time;
		if (time < 10000)
			printf(DEAD1, RED, time, philo->id + 1, ms, philo->nb_meals, RESET);
		else
			printf(DEAD2, RED, time, philo->id + 1, ms, philo->nb_meals, RESET);
		pthread_mutex_unlock(&info->starvation);
		printf("%s%s\n%s", GRAY, DASH, RESET);
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->write);
}

void	print_think(t_info *info, t_philo *philo)
{
	long	time;
	int		nb_meal;

	nb_meal = philo->nb_meals + 1;
	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->satiated);
	if (check_end(info) && (info->satiated_nb <= info->nb_philo))
	{
		time = philo_time() - info->start_time;
		if (time < 10000)
			printf(THINK1, WHITE, time, philo->id + 1, nb_meal, RESET);
		else
			printf(THINK2, WHITE, time, philo->id + 1, nb_meal, RESET);
		printf("%s%s\n%s", GRAY, DASH, RESET);
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->write);
}

void	print_sleep(t_info *info, t_philo *philo)
{
	long	time;
	int		nb_meal;

	nb_meal = philo->nb_meals + 1;
	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->satiated);
	if (check_end(info) && (info->satiated_nb <= info->nb_philo))
	{
		time = philo_time() - info->start_time;
		if (time < 10000)
			printf(SLEEP1, WHITE, time, philo->id + 1, nb_meal, RESET);
		else
			printf(SLEEP2, WHITE, time, philo->id + 1, nb_meal, RESET);
		printf("%s%s\n%s", GRAY, DASH, RESET);
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->write);
}

void	print_fork(t_info *info, t_philo *philo, int fork)
{
	long	time;
	int		nb_philo;
	int		nb_meal;

	nb_philo = info->nb_philo;
	nb_meal = philo->nb_meals + 1;
	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->satiated);
	if (check_end(info) && (info->satiated_nb <= nb_philo || nb_philo == 1))
	{
		time = philo_time() - info->start_time;
		if (time < 10000)
			printf(FORK1, WHITE, time, philo->id + 1, fork + 1, nb_meal, RESET);
		else
			printf(FORK2, WHITE, time, philo->id + 1, fork + 1, nb_meal, RESET);
		printf("%s%s\n%s", GRAY, DASH, RESET);
	}
	pthread_mutex_unlock(&info->satiated);
	pthread_mutex_unlock(&info->write);
}

void	print_meal(t_info *info, t_philo *philo, int count)
{
	long	time;

	pthread_mutex_lock(&info->write);
	pthread_mutex_lock(&info->starvation);
	if (check_end(info) && (info->satiated_nb <= info->nb_philo))
	{
		time = philo_time() - info->start_time;
		if (time <= 401)
			philo->starvation_time = info->time_die;
		print_meals(info, philo, count, time);
		printf("%s%s\n%s", GRAY, DASH, RESET);
		philo->starvation_time = time + info->time_die;
	}
	pthread_mutex_unlock(&info->starvation);
	pthread_mutex_unlock(&info->write);
}
