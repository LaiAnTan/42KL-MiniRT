NAME = minirt

CDIR = srcs

ODIR = obj

SRCS_C =	srcs/utils/utils_atof.c				\
			srcs/utils/utils_get_next_line.c	\
			srcs/utils/utils_split.c			\
			srcs/utils/utils.c					\
			srcs/file.c							\
			srcs/main.c							\
			srcs/scene_objects.c				\
			srcs/vec3.c							\
			srcs/vec4.c							\
			srcs/matrix.c						\
			srcs/ray.c							\
			srcs/mlx.c							\
			srcs/view.c	\
			srcs/pixel_to_view.c	\

SRCS_O = $(SRCS_C:.c=.o)

CFLAG = -Wall -Wextra -Werror

# FSAN = -fsanitize=address -g

LIB = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all : $(NAME) move

%.o:%.c
		@gcc $(CFLAG) -I/usr/include -Imlx_linux -O3 -c $< -o $(<:.c=.o)

$(NAME): $(SRCS_O)
		@gcc $(SRCS_O) $(CFLAG) $(LIB) $(FSAN) -o $(NAME) 

$(ODIR) :
	@echo "Folder $(ODIR) does not exist, making a new one..."
	@mkdir $@

move : $(ODIR)
	@clear
	@echo "Storing object files into $(ODIR)..."
	@mv $(SRCS_O) $(ODIR)
	

run :
	@./$(NAME)

vg :
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean :
	@echo "Removing object files..."
	@rm -f $(ODIR)/*.o

fclean : clean
	@echo "Removing executable $(NAME) and folder $(ODIR)..."
	@rm -f $(NAME)
	@rmdir $(ODIR)

re : fclean all

.PHONY: all clean fclean re git $(NAME)
