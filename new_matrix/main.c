#include "matrix.h"
#include "vector.h"

// int main()
// {
// 	matrix_type	values[] = {0,1,2,3,4,5,6,7,8};
// 	matrix_type	values2[] = {2,3,4,1,2,3,6,7,8};

// 	t_matrix	*stuff;
// 	stuff = init_matrix(values, 3, 3);
// 	t_matrix	*stuff2;
// 	stuff2 = init_matrix(values2, 3, 3);

// 	t_matrix	*ret;

// 	printf("Stuff1 = \n");
// 	m_print_matrix(stuff);

// 	printf("\n");

// 	printf("Stuff2 = \n");
// 	m_print_matrix(stuff2);

// 	printf("\n");

// 	printf("Addition = \n");
// 	ret = m_addition(stuff, stuff2);
// 	m_print_matrix(ret);
// 	free_matrix(&ret);

// 	printf("\n");

// 	printf("Substraction = \n");
// 	ret = m_substraction(stuff, stuff2);
// 	m_print_matrix(ret);
// 	free_matrix(&ret);

// 	printf("\n");

// 	printf("Multiplication = \n");
// 	ret = m_multiplication(stuff, stuff2);
// 	m_print_matrix(ret);
// 	free_matrix(&ret);

// 	printf("\n");
// 	printf("Empty Matrix = \n");
// 	ret = init_empty_matrix(3, 2);
// 	m_print_matrix(ret);
// 	free_matrix(&ret);

// 	printf("\n");
// 	matrix_type	value3[] = {1,2,3,4};
// 	matrix_type	value4[] = {5,2,3,5,1,3,6,7,8,2,1,3,3,1,2,3};

// 	t_matrix	*stuff3 = init_matrix(value3, 1, 4);
// 	t_matrix	*stuff4 = init_matrix(value4, 4, 4);

// 	printf("Stuff3 = \n");
// 	m_print_matrix(stuff3);

// 	printf("\n");

// 	printf("Stuff4 = \n");
// 	m_print_matrix(stuff4);

// 	printf("\n");

// 	printf("Multiplication = \n");
// 	ret = m_multiplication(stuff4, stuff3);
// 	m_print_matrix(ret);
// 	free_matrix(&ret);


// 	free_matrix(&stuff);
// 	free_matrix(&stuff2);
// 	free_matrix(&stuff3);
// 	free_matrix(&stuff4);
// }


// matrix epic poggers;

int main()
{
	matrix_type	stuff1[3] = {9,3,1};
	matrix_type	stuff2[3] = {5,2,6};
	t_vector	*vec1 = init_vector_intarr(stuff1);
	t_vector	*vec2 = init_vector_intarr(stuff2);
	t_vector	*result;

	printf("Vector 1: \n");
	print_vector(vec1);
	printf("Vector 2: \n");
	print_vector(vec2);
	printf("Addtion = \n");
	print_vector(v_addition(vec1, vec2));
	printf("Substraction = \n");
	print_vector(v_difference(vec1, vec2));
	printf("Dot Proct = \n");
	printf("%f\n", v_dotproduct(vec1, vec2));
	printf("Project vec1 on vec2 = \n");
	print_vector(v_projection(vec1, vec2));
}
