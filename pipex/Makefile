
NAME = pipex

SRCS = pipex.c \
		ft_exec.c   \
		ft_finder.c \

B_SRCS = pipex_bonus.c \
		 ft_exec.c   \
		ft_finder.c \
		pipex_bonus_utils.c


CC = cc

CFLAGS = -Wall -Wextra -Werror -I ./sources/libft



OFILES = ${SRCS:.c=.o}

B_OFILES = ${B_SRCS:.c=.o}



LIBFT = ./sources/libft

all : mandatory

mandatory : .mandatory

.mandatory : ${OFILES}
	${MAKE} -C ${LIBFT}
	${CC} -o ${NAME} ${CFLAGS} ${OFILES} ${LIBFT}/libft.a
	@touch .mandatory
	@rm -f .bonus

bonus : .bonus

.bonus : ${B_OFILES}
	${MAKE} -C ${LIBFT}
	${CC} -o ${NAME} ${CFLAGS} ${B_OFILES} ${LIBFT}/libft.a
	@touch .bonus
	@rm -f .mandatory

%.o: %.c
	${CC} ${CFLAGS} ${DEPSFLAGS} -c -o $@ $<

-include 

clean :
	rm -f ${OFILES}  ${B_OFILES} 
	${MAKE} -C ${LIBFT} clean
	@rm -f .bonus .mandatory	

fclean :
	rm -f ${NAME} ${OFILES}  ${B_OFILES} 
	${MAKE} -C ${LIBFT} fclean
	@rm -f .bonus .mandatory

re : fclean all

redeps:
	touch 
	make
	${MAKE} -C ${LIBFT} redeps

.PHONY: all clean fclean re redeps libft
