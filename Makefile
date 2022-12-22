# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2022/12/22 12:19:42 by mweverli      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME		:=	philo_test

OBJ_DIR		:=	OBJ
SRC_DIR		:=	src
INC_DIR		:=	include
LIB_DIR		:=	lib

SRC			:=	main.c

OBJ			:=	$(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))

#SRC			:=	$(addprefix $(SRC_DIR)/,$(SRC))

#============== LIBRARIES ===============#

LIB_LIST	:=

#============= DEPENDENCIES =============#

DEP		:=	$(OBJ:.o=.d)

-include $(DEP)

#============= COMPILATION ==============#

INCLUDE		:=	-I $(INC_DIR)

LIBRARY		:=	-lpthread

ifdef DEBUG
CFL			:=	-Wall -Werror -Wextra -g -fsanitize=address
else
CFL			:=	-Wall -Werror -Wextra
endif
CC			:=	gcc

COMPILE		:=	$(CC) $(CFL)

#=============== COLOURS ================#

BOLD	:= \033[1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
CYAN	:= \033[36;1m
RESET	:= \033[0m

#========================================#
#============== RECIPIES  ===============#
#========================================#

echo:
	@echo $(DEP) 

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(NAME): $(LIB_LIST) $(OBJ)
	@$(COMPILE) $(INCLUDE) $(LIBRARY) $(OBJ) -o $(NAME) $(LIB_LIST)
	@echo "$(CYAN)$(BOLD)COMPILING COMPLETE$(RESET)"

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $< 
	@echo "$(CYAN)COMPILING: $(notdir $<)$(if $(findstring -g,$(CFL)), -g) \
		$(RESET)"

debug:
	@$(MAKE) DEBUG=1 all

rebug: fclean debug

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"

fclean: clean 
	@rm -f $(NAME)

re: fclean all

#========================================#
#============== LIBRARIES ===============#
#========================================#

#$(LIB_LIB_ARC):
#	@make -C $(LIB_LIBFT)

#========================================#
#============ MISCELLANEOUS =============#
#========================================#

.PHONY: all clean fclean tclean re test

.DEFAULT_GOAL := all
