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
	token_assignword_updater.c
TEST_SRC := \
	lexer_tester.c

LIBFT = ../../lib/libft/libft.a

LIB_INCLUDE_DIR += -I $(shell brew --prefix readline)/include
LIB_INCLUDE_DIR += -I ../../lib/libft/include

LDFLAGS+= -lreadline -L $(shell brew --prefix readline)/lib/
LDFLAGS+= $(LIBFT)

all:
	$(MAKE) $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(addprefix ../../src/lexer/, $(SRC)) $(TEST_SRC) $(LIB_INCLUDE_DIR) -I $(INCLUDE_DIR) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C ../../lib/libft

clean:
	rm -f $(NAME)

fclean: clean
	$(MAKE) fclean -C ../../lib/libft

re: fclean all

.PHONY: clean fclean re paco
