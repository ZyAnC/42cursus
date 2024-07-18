
NAME = pipex

SRCS = ./pipex.c
	


CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./sources/libft

DEPSFLAGS += -MMD -MP

OFILES = ${SRCS:.c=.o}



DEPS = ${SRCS:.c=.d}



LIBFT = ./sources/libft

all : mandatory

mandatory : .mandatory

.mandatory : ${OFILES}
	${MAKE} -C ${LIBFT}
	${CC} -o ${NAME} ${CFLAGS} ${OFILES} ${LIBFT}/libft.a



%.o: %.c
	${CC} ${CFLAGS} ${DEPSFLAGS} -c -o $@ $<

-include ${DEPS}

clean :
	rm -f ${OFILES} ${DEPS} 
	${MAKE} -C ${LIBFT} clean
	@rm -f  .mandatory	

fclean :
	rm -f ${NAME} ${OFILES} ${DEPS} 
	${MAKE} -C ${LIBFT} fclean
	@rm -f  .mandatory

re : fclean all

redeps:
	touch ${DEPS}
	make
	${MAKE} -C ${LIBFT} redeps

.PHONY: all clean fclean re redeps libft