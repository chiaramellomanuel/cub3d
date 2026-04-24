NAME			:= cub3d
NAME_BONUS		:= cub3d_bonus
LIBFT			:= libft/libft.a
CC				:= cc
CFLAGS			:= -Wall -Werror -Wextra -I./include
RM				:= rm -rf
LIB				:= ft
SRC_DIR			:= src
SRC_DIR_BONUS	:= src_bonus
BUILD_DIR		:= .build
BUILD_DIR_BONUS	:= .build_bonus
DIR_MKD			:= mkdir -p
INCLUDES 		:= -I/usr/include -Imlx_linux
MLX_FLAGS		:= -L./mlx_linux -lmlx -lXext -lX11 -lm

SRCS		:=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/keys.c \
				$(SRC_DIR)/rays.c \
				$(SRC_DIR)/draw.c \
				$(SRC_DIR)/movements.c \
				$(SRC_DIR)/init_struct.c \
				$(SRC_DIR)/texture_utils/texture.c \
				$(SRC_DIR)/texture_utils/init_texture.c \
				$(SRC_DIR)/parsing/parse_init/parse_init.c \
				$(SRC_DIR)/parsing/cub_parsing/cub_check.c \
				$(SRC_DIR)/parsing/path_parsing/texture_path.c \
				$(SRC_DIR)/parsing/path_parsing/missing_path_print.c \
				$(SRC_DIR)/parsing/map_parsing/map_parsing.c \
				$(SRC_DIR)/parsing/map_parsing/check_map_validity.c \
				$(SRC_DIR)/parsing/map_parsing/check_enclosed_map.c \
				$(SRC_DIR)/parsing/utility/free_mem.c \
				$(SRC_DIR)/parsing/utility/print_error.c

SRCS_BONUS	:= 	$(SRC_DIR_BONUS)/main.c \
				$(SRC_DIR_BONUS)/keys.c \
				$(SRC_DIR_BONUS)/rays.c \
				$(SRC_DIR_BONUS)/draw.c \
				$(SRC_DIR_BONUS)/mouse.c \
				$(SRC_DIR_BONUS)/minimap.c \
				$(SRC_DIR_BONUS)/movements.c \
				$(SRC_DIR_BONUS)/init_struct.c \
				$(SRC_DIR_BONUS)/texture_utils/texture.c \
				$(SRC_DIR_BONUS)/texture_utils/init_texture.c \
				$(SRC_DIR_BONUS)/parsing/parse_init/parse_init.c \
				$(SRC_DIR_BONUS)/parsing/cub_parsing/cub_check.c \
				$(SRC_DIR_BONUS)/parsing/path_parsing/texture_path.c \
				$(SRC_DIR_BONUS)/parsing/path_parsing/missing_path_print.c \
				$(SRC_DIR_BONUS)/parsing/map_parsing/map_parsing.c \
				$(SRC_DIR_BONUS)/parsing/map_parsing/check_map_validity.c \
				$(SRC_DIR_BONUS)/parsing/map_parsing/check_enclosed_map.c \
				$(SRC_DIR_BONUS)/parsing/utility/free_mem.c \
				$(SRC_DIR_BONUS)/parsing/utility/print_error.c

OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
OBJS_BONUS	:= $(SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(BUILD_DIR_BONUS)/%.o)

LDFLAGS		:= $(addprefix -L,$(dir $(LIBFT)))
LDLIB		:= $(addprefix -l,$(LIB))

all	: $(LIBFT) header $(NAME)

$(NAME): $(OBJS) $(LIBFT)
			$(CC) $(LDFLAGS) $^ $(LDLIB) -o $@ $(MLX_FLAGS) \
		&& echo "${BOLD}${GREEN}Done!${NO_COLOR}" || echo "${BOLD}${RED}Error compiling $(NAME)${NO_COLOR}";

bonus	: $(LIBFT) header_bonus $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
			$(CC) $(LDFLAGS) $^ $(LDLIB) -o $@ $(MLX_FLAGS) \
		&& echo "${BOLD}${GREEN}Done!${NO_COLOR}" || echo "${BOLD}${RED}Error compiling $(NAME_BONUS)${NO_COLOR}";

$(LIBFT):
	$(MAKE) -C $(@D)
	$(MAKE) bonus -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
			$(DIR_MKD) $(@D)
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c
			$(DIR_MKD) $(@D)
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
		$(MAKE) clean -C libft
		$(RM) $(BUILD_DIR)
		$(RM) $(BUILD_DIR_BONUS)

fclean: clean
		$(MAKE) fclean -C libft
		$(RM) $(NAME)
		$(RM) $(NAME_BONUS)

re: fclean all

header: 
	${info }
	${info ${BOLD}Creating  ->${YELLOW}$(NAME)${NO_COLOR}}
	@if $(MAKE) -q $(NAME) ; then \
		echo "${BOLD}${YELLOW}No changes detected, not rebuilding $(NAME)${NO_COLOR}"; \
	fi

header_bonus: 
	${info }
	${info ${BOLD}Creating  ->${YELLOW}$(NAME_BONUS)${NO_COLOR}}
	@if $(MAKE) -q $(NAME_BONUS) ; then \
		echo "${BOLD}${YELLOW}No changes detected, not rebuilding $(NAME_BONUS)${NO_COLOR}"; \
	fi

.PHONY: all re clean fclean bonus header header_bonus
.SILENT:

YELLOW		:= ${shell tput setaf 3}
GREEN		:= ${shell tput setaf 2}
RED			:= ${shell tput setaf 1}
NO_COLOR	:= ${shell tput sgr0}
BOLD		:= ${shell tput bold}

