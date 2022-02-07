# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 13:21:26 by mhirabay          #+#    #+#              #
#    Updated: 2022/02/07 13:51:10 by tkirihar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= minishell
SRCDIR 	:= ./src/
SRCNAME	:=	main_test.c \
			execute_builtin.c \
			execute_self.c \
			self_pwd.c \
			self_cd.c \
			self_echo.c \
			self_env.c \
			self_export.c \
			error_handling.c \
			redirect_process.c \
			debug.c \
			env.c \
			kvs.c \
			export.c \
			init.c \
			lst_utils.c \


SRCS	:= $(addprefix $(SRCDIR), $(SRCNAME))
OBJSDIR	:= ./obj/
OBJS 	:= $(addprefix $(OBJSDIR), $(SRCNAME:%.c=%.o))

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra
DEBUG	:= -g -fsanitize=address
INC		:= -I ./includes/
RM		:= rm -rf
LDFLAGS := -Llib/ft_printf -Llib/gnl -Llib/libft -Llib/ft_lst
LIBS 	:= -lftprintf -lgnl -lft -llst

all: lib $(NAME)

lib :
	make -C lib/ft_printf
	make -C lib/gnl
	make -C lib/libft
	make -C lib/ft_lst

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INC) ${LDFLAGS} ${LIBS} $^ -o $@

$(OBJSDIR)%.o : $(SRCDIR)%.c
	@if [ ! -d $(OBJSDIR) ]; then mkdir $(OBJSDIR); fi
	${CC} ${CFLAGS} $(INC) -c $< -o $@

clean:
	make clean -C lib/ft_printf
	make clean -C lib/libft
	make clean -C lib/ft_lst
	$(RM) $(OBJSDIR)

fclean: clean
	make fclean -C lib/ft_printf
	make fclean -C lib/libft
	make fclean -C lib/ft_lst
	${RM} ${NAME}
re:	fclean all

debug:	CFLAGS += $(DEBUG)
debug:	re

.PHONY: all clean fclean re debug lib