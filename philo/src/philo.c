/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:14:31 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/23 02:49:24 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	philo_alone(t_info *info)
{
	t_philo	philo;

	philo = info->philos[0];
	if (pthread_create(&philo.thread, NULL, routine_philo, &philo))
		return (philo_error("Error: phtread_create failed\n", FAILURE));
	philo.starvation_time = info->time_die;
	print_fork(info, &philo, philo.left_fork_id);
	philo_sleep(info, info->time_die);
	print_death(info, &philo);
	pthread_join(philo.thread, NULL);
	free(info->philos);
	end_mutexes(info);
	return (SUCCESS);
}

static int	philo(t_info *info)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = info->philos;
	printf("%s%s%s%s\n", WHITE, DASH, DASH2, RESET);
	info->start_time = philo_time();
	if (info->nb_philo == 1)
		return (philo_alone(info));
	if (pthread_create(&info->satiated_id, NULL, routine_satiated, &info))
		return (philo_error("Error: phtread_create failed\n", FAILURE));
	if (pthread_create(&info->service_id, NULL, routine_service, &info))
		return (philo_error("Error: phtread_create failed\n", FAILURE));
	while (++i < info->nb_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, routine_philo, &philos[i]))
			return (philo_error("Error: phtread_create failed\n", FAILURE));
		pthread_mutex_lock(&info->time_check);
		philos[i].last_meal_time = philo_time();
		pthread_mutex_unlock(&info->time_check);
	}
	end_program(info);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_args(argc, argv))
		return (FAILURE);
	if (init_info(argv, &info))
		return (FAILURE);
	if (init_philo(&info))
		return (FAILURE);
	if (init_mutex(&info))
		return (FAILURE);
	if (philo(&info))
		return (FAILURE);
	return (SUCCESS);
}
