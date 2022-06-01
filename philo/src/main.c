/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:14:31 by 0xNino            #+#    #+#             */
/*   Updated: 2022/06/01 21:21:49 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	error(char *errmsg, int errnum)
{
	printf("%s", errmsg);
	return (errnum);
}

static int	isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

static int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || 6 < argc)
		return (error("Error: wrong argument count\n", 1));
	i = 1;
	while (i < argc)
	{
		if (isnumber(argv[i]))
			return (error("Error: invalid arguments\n", 1));
		i++;
	}
	return (0);
}

static void	init_info(char **argv, t_info *info)
{
	info->nb_philo = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->nb_meals_req = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_args(argc, argv))
		return (1);
	init_info(argv, &info);
	return (0);
}
