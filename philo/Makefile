SRC		=	main.c \
			philo_utils.c \
			parse.c \
			color.c \
			time.c

OBJS 	=	${SRC:.c=.o}

NAME	=	philo

CC		=	gcc

CFLAGS 	=	-Wall -Wextra -Werror -pthread #-O3 -fsanitize=thread -g

RM	 	=	rm -f

all:		${NAME}

%.o:		%.c
			${CC} ${CFLAGS} -o $@ -c $<


$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $@ $^

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean $(NAME)

.PHONY:		all clean fclean