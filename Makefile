# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhirabay <mhirabay@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 13:21:26 by mhirabay          #+#    #+#              #
#    Updated: 2022/02/01 09:57:31 by mhirabay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= minishell
SRCDIR 	:= ./src/
SRCNAME	:=	main_test.c

SRCS	:= $(addprefix $(SRCDIR), $(SRCNAME))
OBJSDIR	:= ./obj/
OBJS 	:= $(addprefix $(OBJSDIR), $(SRCNAME:%.c=%.o))

CC		:= gcc 
CFLAGS	:= -Wall -Werror -Wextra
DEBUG	:= -g -fsanitize=address
INC		:= -I ./includes/
RM		:= rm -rf

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INC) $^ -o $@

$(OBJSDIR)%.o : $(SRCDIR)%.c
	@if [ ! -d $(OBJSDIR) ]; then mkdir $(OBJSDIR); fi
	${CC} ${CFLAGS} $(INC) -c $< -o $@

clean: 
	$(RM) $(OBJSDIR)

fclean: clean
	${RM} ${NAME} 
re:	fclean all

debug:	CFLAGS += $(DEBUG)
debug:	re

.PHONY: all clean fclean re debug