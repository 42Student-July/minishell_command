# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 13:21:26 by mhirabay          #+#    #+#              #
#    Updated: 2022/02/02 14:36:11 by tkirihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= minishell
SRCDIR 	:= ./src/
SRCNAME	:=	main_test.c \
			execute_builtin.c \
			execute_self.c \


SRCS	:= $(addprefix $(SRCDIR), $(SRCNAME))
OBJSDIR	:= ./obj/
OBJS 	:= $(addprefix $(OBJSDIR), $(SRCNAME:%.c=%.o))

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
DEBUG	:= -g -fsanitize=address
INC		:= -I ./includes/
RM		:= rm -rf
LDFLAGS := -Llib/ft_printf -Llib/gnl -Llib/libft
LIBS 	:= -lftprintf -lgnl -lft

all: lib $(NAME)

lib :
	make -C lib/ft_printf
	make -C lib/gnl
	make -C lib/libft

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INC) ${LDFLAGS} ${LIBS} $^ -o $@

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

.PHONY: all clean fclean re debug lib