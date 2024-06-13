# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eberkowi <eberkowi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 13:52:40 by eberkowi          #+#    #+#              #
#    Updated: 2024/06/06 10:37:51 by eberkowi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = pipex.c ft_split.c commands.c functions.c
OBJECTS= $(SOURCES:.c=.o)
NAME = pipex

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
fclean: clean
	 rm -f $(NAME)
re: fclean $(NAME)

.PHONY: all clean fclean re