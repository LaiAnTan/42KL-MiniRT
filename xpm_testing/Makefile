SRCS = xpm_tester.c xpm_extractor.c vec3.c matrix.c

OBJ = xpm_tester.o xpm_extractor.o vec3.o matrix.o

CC = gcc

NAME = test

%.o: %.c
	$(CC) -I/usr/include -I../mlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx_linux libmlx_Linux.a -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -rf *.o

fclean:
	rm -rf *.o
	rm -rf ${NAME}

re : fclean $(NAME)
