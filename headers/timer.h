#pragma once

#ifndef __TIMER_H__

#define __TIMER_H__

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct timeval		t_val;
typedef long unsigned int	t_ms;

typedef struct	s_timer
{
	t_val		tv;
	t_ms		start;
	t_ms		end;
}			t_timer;

t_timer	*timer_init(void);

void	timer_destroy(t_timer **timer);

void	timer_start(t_timer *timer);
void	timer_end(t_timer *timer);

void	timer_print_diff(t_timer *timer);
void	timer_print_start(t_timer *timer);
void	timer_print_end(t_timer *timer);

#endif