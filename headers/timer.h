/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:00:44 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:09:06 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H

# define TIMER_H

# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct timeval		t_val;
typedef long unsigned int	t_ms;

typedef struct s_timer
{
	t_val		tv;
	t_ms		start;
	t_ms		end;
}	t_timer;

t_timer	*timer_init(void);

void	timer_destroy(t_timer **timer);

void	timer_start(t_timer *timer);
void	timer_end(t_timer *timer);

void	timer_print_diff(t_timer *timer);
void	timer_print_start(t_timer *timer);
void	timer_print_end(t_timer *timer);

#endif