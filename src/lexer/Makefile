NAME = lexer.o
CC := cc
CFLAGS := -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g3
LDFLAGS += -fsanitize=address -g3

INCLUDE_DIR = ../../include

SRC := \
	lexer.c \
	scanner_checker.c \
	scanner_maniputalor.c \
	token_maker.c \
	token_lst_utils.c \
	lexer_tester.c

LIBFT = ../../lib/libft/libft.a

LIB_INCLUDE_DIR += -I $(shell brew --prefix readline)/include
LIB_INCLUDE_DIR += -I ../../lib/libft

LDFLAGS+= -lreadline -L $(shell brew --prefix readline)/lib/
LDFLAGS+= $(LIBFT)

all:
	$(MAKE) $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(SRC) $(LIB_INCLUDE_DIR) -I $(INCLUDE_DIR) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C ../../lib/libft

clean:
	rm -f $(NAME)

fclean: clean
	$(MAKE) fclean -C ../../lib/libft

re: fclean all

.PHONY: clean fclean re paco
