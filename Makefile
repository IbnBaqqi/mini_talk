# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabdulba <sabdulba@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/13 14:26:27 by sabdulba          #+#    #+#              #
#    Updated: 2024/12/14 16:57:59 by sabdulba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minitalk
CC := cc
RM := rm -rf
FLAG := -Wall -Wextra -Werror

LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_DIR := ./lib/libft

HEADERS := -I ./inc -I $(LIBFT_DIR)/inc
LINK := -L$(LIBFT_DIR) -lft

SRC_DIR := src
SRC := $(shell ls src/*.c)

OBJ_DIR := obj
OBJ := $(SRC:src%.c=obj%.o)

SERVER_SRC := $(SRC_DIR)/server.c
CLIENT_SRC := $(SRC_DIR)/client.c
SERVER_OBJ := $(OBJ_DIR)/server.o
CLIENT_OBJ := $(OBJ_DIR)/client.o

all: $(NAME)

$(LIBFT): $(LIBFT_DIR)
	make -C $(LIBFT_DIR);

$(LIBFT_DIR):
	git clone https://github.com/IbnBaqqi/libft.git $@;

$(OBJ_DIR):
	mkdir obj

$(NAME): server client

$(SERVER_OBJ): $(SERVER_SRC) $(LIBFT) | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $(SERVER_SRC) -o $(SERVER_OBJ) $(HEADERS)

$(CLIENT_OBJ): $(CLIENT_SRC) $(LIBFT) | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $(CLIENT_SRC) -o $(CLIENT_OBJ) $(HEADERS)

server: $(SERVER_OBJ) $(LIBFT)
	$(CC) $(SERVER_OBJ) $(LINK) -o server

client: $(CLIENT_OBJ) $(LIBFT)
	$(CC) $(CLIENT_OBJ) $(LINK) -o client

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/minitalk.h
	$(CC) -c $(FLAG) $< -o $@ $(HEADERS)

clean:
	$(RM) $(NAME)
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(LIBFT_DIR)/obj

fclean: clean
	@rm -f $(NAME)
	$(RM) $(OBJ_DIR)
	$(RM) $(LIBFT_DIR)/libft.a
	$(RM) $(LIBFT_DIR)
	$(RM) client server

re: fclean all
