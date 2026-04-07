# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcuenca- <mcuenca-@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/23 16:46:01 by mcuenca-          #+#    #+#              #
#    Updated: 2026/03/31 13:46:02 by dortega-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
CFLAGS= -Wall -Wextra -Werror -Iincludes -Isrcs -Ilibft -Iminilibx-linux -g

LIBFT_DIR=libft
LIBFT= libft/libft.a
MLX_DIR= mlx
MLX= mlx/libmlx.a
LIBS= $(LIBFT) $(MLX) -lXext -lX11 -lm

HEAD=inc/cub.h 

SRCS_DIR= srcs
SRCS= \
	srcs/executer/main.c \
	srcs/executer/moves.c

OBJS_DIR= objs
OBJS= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

NAME= cube3d

all: $(NAME)

$(NAME): $(OBJS) libs
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

libs: $(LIBFT) $(MLX)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEAD) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

vpath %.c is mem print print/print_srcs put str num lst gnl

clean:
	$(MAKE) -C  $(LIBFT_DIR) clean
	$(MAKE) -C  $(MLX_DIR) clean
	rm -f $(OBJS)
	if [ -d $(OBJS_DIR) ]; then rm -drf $(OBJS_DIR); fi

fclean: clean
	$(MAKE) -C  $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
