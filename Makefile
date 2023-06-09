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

SRCS_H = headers/minrt.h

SRCS_O = $(SRCS_C:.c=.o)

# CFLAG = -Wall -Wextra -Werror

# FSAN = -fsanitize=address -g

LIB = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lmlx_Linux

all : $(NAME) move

%.o:%.c
		@gcc $(CFLAG) -c $< -o $(<:.c=.o)

$(NAME): $(SRCS_O)
		@gcc $(CFLAG) -o $(NAME) $(SRCS_O) $(LIB) ${FSAN}

$(ODIR) :
	@echo "Folder $(ODIR) does not exist, making a new one..."
	@mkdir $@

move : $(ODIR)
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