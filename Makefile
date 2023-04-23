################################
######     Variables     #######
################################

NAME:=minishell

CC:=cc
CFLAGS= -Wall -Wextra -Werror
ifdef FSANITIZE
	CFLAGS+= -g3 -fsanitize=address
	LDFLAGS+= -g3 -fsanitize=address
endif

SRC:= \
	main.c
OBJS_DIR:=obj/
OBJS:=${addprefix ${OBJS_DIR}/,${SRC:.c=.o}}
INCLUDE:= \
	include

#################################
######     Main rules     #######
#################################

all:
	${MAKE} ${NAME} -j

${NAME}: ${OBJS}
	@${CC} ${PRINTF} ${OBJS} -o ${NAME} ${LDFLAGS} && echo "Compilation of ${NAME} successful"

${OBJS_DIR}:
	@mkdir -p ${OBJS_DIR}

${OBJS_DIR}%.o: %.c
	@${CC} ${CFLAGS} ${addprefix -I ,${INCLUDE}} -c $< -o $@

bonus: re

###############################
######     Cleaning     #######
###############################

clean: 
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re bonus