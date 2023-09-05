/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:00:27 by tlai-an           #+#    #+#             */
/*   Updated: 2023/09/05 18:08:16 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H

# define MATRIX_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

typedef double	t_matrix_type;

typedef struct s_matrix
{
	t_matrix_type	**m;
	int				x;
	int				y;

}	t_matrix;

t_matrix		*m_init(t_matrix_type *values, int x, int y);
t_matrix		*m_init_empty(int x, int y);
t_matrix		*m_init_identity(int x, int y);
t_matrix		*m_dup(t_matrix *source);
t_matrix		*m_dup_emptymatrix(t_matrix *source);

t_matrix_type	*m_convert_to_1d(t_matrix *source);
t_matrix		*m_addition(t_matrix *left, t_matrix *right);
t_matrix		*m_subtraction(t_matrix *left, t_matrix *right);
t_matrix		*m_multiplication(t_matrix *left, t_matrix *right);

t_matrix		*m_scalar_multi(t_matrix *left, double val);
t_matrix		*m_scalar_divide(t_matrix *left, double val);
t_matrix		*m_transpose(t_matrix *m);
void			free_matrix(t_matrix **t_free);
void			m_print_matrix(t_matrix *m);

#endif