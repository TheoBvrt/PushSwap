NAME = push_swap
SRCS =	./srcs/main.c \
		./srcs/list/list_manager.c \
		./srcs/parser/parser.c \
		./srcs/utils/utils.c \

OBJS = ${SRCS:.c=.o}
CC = gcc
RM = rm -f
CFLAGS = -Iheaders -g

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
