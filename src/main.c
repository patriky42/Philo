/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 09:54:18 by pabastid          #+#    #+#             */
/*   Updated: 2024/02/21 14:52:05 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	if (5 == argc || 6 == argc)
	{
		if (check_errors(argv) != 0)
			return (0);
		data = ft_calloc((argc), sizeof(t_data));
		if (!data)
			exit(1);
		if (giving_data(data, argv) != 0)
			return (free_and_destroy(data, NULL, 0));
		philo = create_philo(data);
		if (!philo)
			return (free_and_destroy(data, philo, 0));
		if (ft_atoi(argv[1]) == 1)
			create_one_philo(data, philo);
		else
			ft_create_thread(data, philo);
		free_and_destroy(data, philo, 0);
	}
	else
		return (ft_error(2));
	return (0);
}
