NAME = minirt

CDIR = srcs

ODIR = obj

SRCS_C =	srcs/utils/utils_2.c				\
			srcs/utils/utils_atof.c				\
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
			srcs/view.c							\
			srcs/model.c						\
			srcs/circle.c						\
			srcs/collision.c					\
			srcs/lighting.c						\
			srcs/plane.c						\
			srcs/raytrace.c						\
			srcs/cylinder.c						\
			srcs/events.c						\
			srcs/timer.c						\
			srcs/viewport.c						\

# CFLAGS := -Wall -Wextra -Werror

# FSAN = -fsanitize=address -g

UNAME := $(shell uname -s)

INCS  :=
	ifeq ($(UNAME), Linux)
		INCS := -Imlx_linux
	endif
	ifeq ($(UNAME), Darwin)
		INCS := -Imlx
	endif

LIBS :=
	ifeq ($(UNAME), Linux)
		LIBS := -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
	endif
	ifeq ($(UNAME), Darwin)
		LIBS := -lmlx -framework OpenGL -framework AppKit
	endif
	
LIBS_O :=
	ifeq ($(UNAME), Linux)
		LIBS_O := -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
	endif
	ifeq ($(UNAME), Darwin)
		LIBS_O := ""
	endif

SRCS_O := $(addprefix $(ODIR)/,$(notdir $(SRCS_C:.c=.o)))

vpath %.c srcs/builtins:srcs/cmd:srcs/redirection:srcs/utils:srcs/vars:srcs

# Colors
L_RESET = \e[1K\r
C_CYAN = \033[0;96m
C_GREEN = \033[0;92m
C_RESET = \033[0m

all : $(NAME)

$(NAME): $(SRCS_O)
	@gcc ${CFLAGS} $^ $(LIBS) -o $@ $(FSAN)
	@printf "$(L_RESET)$(C_GREEN)Done!$(C_RESET)\n"

$(ODIR) :
	@mkdir -p $@

$(ODIR)/%.o: %.c | $(ODIR)
	@gcc $(CFLAGS) $(INCS) $(LIBS_O) -c $< -o $@;
	@printf "$(L_RESET)$(C_RESET)Creating object file $(C_CYAN)$@$(C_RESET) from $(C_CYAN)$<$(C_RESET)"

run :w
	@./$(NAME)

vg :
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) scenes/empty.rt

clean :
	@echo 'Removing executable files...'
	@rm -rf $(NAME)

fclean : clean
	@echo "Removing executable $(NAME) and object file folder $(ODIR)..."
	@rm -f $(NAME)
	@rm -rf $(ODIR)

re : fclean all

.PHONY: all clean fclean re
