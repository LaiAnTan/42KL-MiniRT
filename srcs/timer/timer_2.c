/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:45:42 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/02 10:45:55 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/timer.h"

void	timer_print_diff(t_timer *timer)
{
	printf("Timer: diff: %ld ms\n", timer->end - timer->start);
}

void	timer_print_start(t_timer *timer)
{
	printf("Timer: start: %ld ms\n", timer->start);
}

void	timer_print_end(t_timer *timer)
{
	printf("Timer: end: %ld ms\n", timer->end);
}
