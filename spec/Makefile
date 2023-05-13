################################
######     Variables     #######
################################

NAME:=debug
TARGET_NAME:=minishell
TARGET_DIR:=../

CC:=cc
CFLAGS:= -Wall -Wextra -Werror
ifdef FSANITIZE
	CFLAGS+= -g3 -fsanitize=address
	LDFLAGS+= -g3 -fsanitize=address
endif
INCLUDE_DIR= \
	include \
	../include \
	../lib/libft

###################################
######     Source files     #######
###################################

# To add souce files, create a varaible for each folder, and then
# contatenate them in the SRC variable like this:

TEST_SRC:= \
	expander.c
MAIN_SRC:= \
	main.c
SRC:= $(TEST_SRC) $(MAIN_SRC)

####################################
######     Library files     #######
####################################

# To compile a library, store a variable for their library file like this
# and add a rule for it after the main rules:
# LIBRARY_NAME=lib/LIBRARY_NAME/LIBRARY_NAME.a
TARGET= $(TARGET_DIR)/lib$(TARGET_NAME).so
LIBFT=../lib/libft/libft.a

# To add a library, add the library header file like this:
# LIB_INCLUDE_DIR+= $(shell brew --prefix readline)/include

# Then add the library to the linking process in one of the following ways:
# LDFLAGS+= -Llib/LIBRARY_NAME -lLIBRARY_NAME
# LDFLAGS+= lib/LIBRARY_NAME/libLIBRARY_NAME.a
LDFLAGS+= -l$(TARGET_NAME) -L $(TARGET_DIR)
LDFLAGS+= $(LIBFT)

###########################################
######     Object name reformat     #######
###########################################

# This in effect makes all the object files to be compiled in the OBJ_DIR directory

SRC_DIR:=tests
OBJ_DIR:=obj
OBJ:= $(addprefix $(OBJ_DIR)/,$(subst /,@,$(SRC:.c=.o)))

#################################
######     Main rules     #######
#################################

all:
	@$(MAKE) $(NAME) -j

$(NAME): $(TARGET) $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS) && \
	ln -sf $(TARGET) ./lib$(TARGET_NAME).so && \
	echo "Compilation of $(NAME) successful"

bonus: re

##########################################
######     Library compilation     #######
##########################################

# To compile a library, add a rule like this:

$(TARGET):
	@$(MAKE) $(if $(FSANITIZE),FSANITIZE=yes,) -C $(TARGET_DIR) repack

# $(LIBRARY_NAME):
# 	@${MAKE} $(if $(FSANITIZE),FSANITIZE=yes,) -C lib/LIBRARY_NAME

#########################################
######     Object compilation     #######
#########################################

.SECONDEXPANSION:
$(OBJ_DIR)/%.o: $(SRC_DIR)/$$(subst @,/,$$*).c
	@$(CC) $(CFLAGS) $(addprefix -iquote ,$(INCLUDE_DIR)) $(addprefix -I ,$(LIB_INCLUDE_DIR)) -c $< -o $@

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

###############################
######     Cleaning     #######
###############################

clean: 
	@rm -f $(OBJ)

fclean: clean
	@rm -f lib$(TARGET_NAME).so
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus $(TARGET)