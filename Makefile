# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 15:59:15 by mtarza            #+#    #+#              #
#    Updated: 2025/02/27 04:41:59 by mtarza           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

CC			= cc
CFLAGS		= -Wall -Wextra -Werror 

SRC_DIR		= start
OBJ_DIR		= obj
LIBFT_DIR	= libft

MLX_DIR		= /usr/include/minilibx-linux

SRCS		= main.c \
			  check_path.c \
			  finish.c \
			  handle_argument.c \
			  handl_error.c \
			  load_all.c \
			  player_mov.c \
			  read_map.c \
			  render_map.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

LIBFT		= $(LIBFT_DIR)/libft.a
LIBFTPRINTF	= $(LIBFT_DIR)/ft_printf/libftprintf.a
MLX			= $(MLX_DIR)/libmlx.a

INCLUDES	= -I$(LIBFT_DIR) -I$(MLX_DIR)
LIBS		= -L$(LIBFT_DIR) -lft -L$(LIBFT_DIR)/ft_printf -lftprintf \
			  -L$(MLX_DIR) -lmlx -lXext -lX11

RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
NC			= \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(LIBFTPRINTF) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully compiled!$(NC)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "$(YELLOW)Compiling $<...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR)

$(LIBFTPRINTF):
	@echo "$(YELLOW)Building ft_printf...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR)/ft_printf

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@find . -name "*.o" -delete


fclean: clean
	@echo "$(RED)Cleaning everything...$(NC)"
	@rm -f $(NAME)
	@find . -name "*.o" -delete
	@find . -name "*.a" -delete




re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS) $(OBJ_DIR)
