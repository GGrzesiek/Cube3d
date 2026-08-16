NAME = cube3d

CC = cc
CFLAGS = #-Wall -Wextra -Werror

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/

SRC = main.c \
		parsing/parse_scene.c \
		parsing/parse_color.c \
		parsing/parse_map.c \
		parsing/parsing_utils.c \
		parsing/create_map.c \
		parsing/map_validation.c \
		parsing/list_utils.c

SRCS   = $(addprefix $(SRC_PATH), $(SRC))
OBJ    = $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
NC = \033[0m

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	@echo "$(BLUE)Created object directories$(NC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(LIBFT_PATH) clean
	@echo "$(RED)Object files cleaned$(NC)"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	@echo "$(RED)Executable cleaned$(NC)"

re: fclean all

.PHONY: all clean fclean re