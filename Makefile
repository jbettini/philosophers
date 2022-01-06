NAME = philo
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g

SRCS	=	${wildcard *.c}	

OBJS = ${SRCS:.c=.o}

%.o: %.c
		${CC} ${CFLAGS} -o $@ -c $?

${NAME}:	${OBJS}	
			${CC} -o ${NAME} ${OBJS}

all:	${NAME} 

clean:
	${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:	fclean all


.PHONY: all clean fclean re
