NAME := so_long
CC := cc
CFLAGS := -Wall -Wextra -Werror -Wunreachable-code -Ofast -fPIC \
	-I ./include -I ./src/libft -I ./src/printf -I ./src/get_next_line -I ./MLX42/include
LIBFT := ./src/libft
PRINTF := ./src/printf
GETNEXTLINE := ./src/get_next_line
LIBMLX := ./MLX42

LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm \
	$(LIBFT)/libft.a $(PRINTF)/libftprintf.a $(GETNEXTLINE)/get_next_line.a

SRCS := so_long.c parsingmap.c parsingmap_utils.c map_algorithm.c initgame.c initgame_util.c  delete.c hook.c\
	$(shell find ./src -iname "*.c")

OBJS := ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	${MAKE} -C ${LIBFT}
	${MAKE} -C ${PRINTF}
	${MAKE} -C ${GETNEXTLINE}
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	${MAKE} -C ${LIBFT} clean
	${MAKE} -C ${PRINTF} clean
	${MAKE} -C ${GETNEXTLINE} clean
	@rm -f .mandatory

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx
