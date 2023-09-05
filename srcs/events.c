/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:27 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 14:44:29 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

// for linux
// 0xff1b = ESC
// 0x72 = r
int	keypress_event_linux(int key_symbol, t_data *data)
{
	if (key_symbol == 0xff1b)
	{
		printf("ESC pressed, exiting...\n");
		clean_exit(data);
	}
	if (key_symbol == 0x72)
	{
		printf("R pressed, commencing re-render...\n");
		do_render_once(data);
	}
	return (0);
}

int	keypress_event_mac(int key_symbol, t_data *data)
{
	if (key_symbol == 0xff1b)
	{
		printf("ESC pressed, exiting...\n");
		clean_exit(data);
	}
	if (key_symbol == 0x72)
	{
		printf("R pressed, commencing re-render...\n");
		do_render_once(data);
	}
	return (0);
}
