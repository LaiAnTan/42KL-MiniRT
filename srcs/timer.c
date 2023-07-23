/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:42:27 by tlai-an           #+#    #+#             */
/*   Updated: 2023/07/23 11:42:28 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/timer.h"

t_timer	*timer_init(void)
{
	t_timer *new_timer;

	new_timer = (t_timer *) malloc(sizeof(t_timer));
	new_timer->start = 0;
	new_timer->end = 0;
	return (new_timer);
}

void	timer_destroy(t_timer **timer)
{
	if (!timer || !*timer) 
		return ;
	free(*timer);
	*timer = NULL;
}

void	timer_start(t_timer *timer)
{
	gettimeofday(&timer->tv, NULL);
	timer->start = ((timer->tv.tv_sec * 1000000) + timer->tv.tv_usec) / 1000;
}

void	timer_end(t_timer *timer)
{
	gettimeofday(&timer->tv, NULL);
	timer->end = ((timer->tv.tv_sec * 1000000) + timer->tv.tv_usec - timer->end) / 1000;
}

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