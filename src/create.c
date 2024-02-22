/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 11:18:50 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/22 12:42:59 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = ft_calloc((data->philos_num), sizeof(t_philo));
	if (!philo)
		exit(1);
	while (i < data->philos_num)
	{
		philo[i].num_philo = i + 1;
		philo[i].fork_left = i;
		philo[i].fork_right = i + 1;
		if (i + 1 == data->philos_num)
			philo[i].fork_right = 0;
		philo[i].data = data;
		philo[i].last_eat = get_time();
		i++;
	}
	return (philo);
}

void	*if_only_one_philo(void *argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
	printing(2, philo);
	ft_sleep(philo->data->time_to_die);
	printf(BRED "%lld Philo has died 💀\n" RESET, (get_time()
			- philo->data->start_time));
	return (NULL);
}

int	create_one_philo(t_data *data, t_philo *philo)
{
	pthread_t	the_philo;

	if (pthread_create(&the_philo, NULL, &if_only_one_philo, philo) != 0)
	{
		printf("Can't create the philo\n");
		return (free_and_destroy(data, philo, 0));
	}
	pthread_join(the_philo, NULL);
	return (0);
}

int	ft_create_thread(t_data *data, t_philo *philos)
{
	pthread_t	*threads;
	int			count_threads;

	count_threads = 0;
	threads = ft_calloc((data->philos_num), sizeof(pthread_t));
	if (!threads)
		return (free_and_destroy(data, philos, 0));
	pthread_mutex_lock(&data->start);
	while (data->philos_num > count_threads)
	{
		if (pthread_create(&threads[count_threads], NULL, &routine,
				&philos[count_threads]) != 0)
			return (free_and_destroy(data, philos, 0));
		count_threads++;
	}
	pthread_mutex_unlock(&data->start);
	create_control(data, philos);
	count_threads = 0;
	while (threads[count_threads])
	{
		pthread_join(threads[count_threads], NULL);
		count_threads++;
	}
	free(threads);
	return (0);
}
