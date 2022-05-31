/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 0xNino <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:14:31 by 0xNino            #+#    #+#             */
/*   Updated: 2022/05/27 15:52:20 by 0xNino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

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

int	main(int argc, char **argv)
{
	if (check_args(argc, argv))
		return (1);
	return (0);
}
