NAME = so_long
SRCS = so_long.c parsingmap.c parsingmap_utils.c map_algorithm.c
CC = cc
CFLAGS = -Wall -Wextra -Werror  -fPIC -I ./src/libft -I ./src/printf -I ./src/get_next_line
OFILES = ${SRCS:.c=.o}
LIBFT = ./src/libft
PRINTF = ./src/printf
GETNEXTLINE = ./src/get_next_line

all : mandatory

mandatory: .mandatory

.mandatory: ${OFILES}
	${MAKE} -C ${LIBFT}
	${MAKE} -C ${PRINTF}
	${MAKE} -C ${GETNEXTLINE}
	${CC} -o ${NAME} ${CFLAGS} ${OFILES} ${LIBFT}/libft.a ${PRINTF}/libftprintf.a ${GETNEXTLINE}/get_next_line.a
	@touch .mandatory

clean :
	rm -f ${OFILES}
	${MAKE} -C ${LIBFT} clean
	${MAKE} -C ${PRINTF} clean
	${MAKE} -C ${GETNEXTLINE} clean
	@rm -f .mandatory

fclean: clean
	rm -f ${NAME}

re: fclean all
