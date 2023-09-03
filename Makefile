NAME = minirt

CDIR = srcs

ODIR = obj

SRCS_C =							\
			main.c					\
			file.c					\
			file_object_handlers.c	\
			file_object_handlers_2.c\
			file_utils.c			\
			scene.c					\
			scene_objects.c			\
			scene_objects_2.c		\
			scene_others.c			\
			scene_free.c			\
			scene_free_2.c			\
			scene_stats.c			\
			scene_stats_2.c			\
			mlx.c					\
			events.c				\
			raytrace.c				\
			view.c					\
			viewport.c				\
			viewport_2.c			\
			ray.c					\
			vec3.c					\
			vec3_2.c				\
			vec3_3.c				\
			vec3_4.c				\
			vec3_5.c				\
			vec4.c					\
			vec4_2.c				\
			vec4_3.c				\
			vec4_4.c				\
			timer.c					\
			timer_2.c				\
			matrix.c				\
			matrix_2.c				\
			matrix_3.c				\
			collision.c				\
			sphere.c				\
			plane.c					\
			cone.c					\
			cylinder.c				\
			lighting_main.c			\
			lighting_ambient.c		\
			lighting_diffuse.c		\
			lighting_specular.c		\
			utils.c					\
			utils_2.c				\
			utils_3.c				\
			utils_atof.c			\
			utils_split.c			\
			utils_get_next_line.c	\
			xpm_extractor.c			\
			obj_color.c				\

CFLAGS := -Wall -Wextra -Werror

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

vpath %.c srcs/utils:srcs/lighting:srcs/object_intersection:srcs:srcs/matrix:srcs/vec3:srcs/vec4:srcs/file:srcs/scene:srcs/timer:srcs/view_matrix

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
