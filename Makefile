NAME = push_swap
SRCS =	./srcs/main.c \
		./srcs/algo.c \
		./srcs/sort.c \
		./srcs/list/list_manager.c \
		./srcs/parser/parser.c \
		./srcs/utils/utils.c \
		./srcs/utils/algo_utils.c \
		./srcs/operations/push.c \
		./srcs/operations/rotate.c \
		./srcs/operations/swap.c \

OBJS = ${SRCS:.c=.o}
CC = gcc
RM = rm -f
CFLAGS = -Iheaders -Wall -Wextra -Werror -g

all : ${NAME}

%.o : %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJS}
	${MAKE} -C ./libft
	$(CC) $(OBJS) ./libft/libft.a -o $(NAME)

clean:
	${RM} ${OBJS}
	make clean -C ./libft

fclean: clean
	${RM} ${NAME}
	make fclean -C ./libft

re: fclean all
