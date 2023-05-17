# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2023/05/17 18:01:47 by mweverli      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME		:=	philosophers

OBJ_DIR		:=	OBJ
SRC_DIR		:=	src
INC_DIR		:=	include
LIB_DIR		:=	lib

SRC			:=	philo.c

SRC			:=	$(SRC:%.c=$(SRC_DIR)/philosophers/%)
OBJ			:=	$(notdir $(SRC:.c=.o))
OBJ			:=	$(OBJ:%=$(OBJ_DIR)/%)
DEP			:=	$(OBJ:.o=.d)

-include $(DEP)

#============== LIBRARIES ===============#

LIB_LIST	:=

#============= COMPILATION ==============#

INCLUDE		:=	-I $(INC_DIR)
LIBRARY		:=	-lpthread

CC			:=	gcc
CFL			:=	-Wall -Werror -Wextra

ifdef DEBUG
CFL			+=	-g -fsanitize=address
endif

COMPILE		:=	$(CC) $(CFL)

#========================================#
#============== RECIPIES  ===============#
#========================================#

echo:
	@echo $(SRC) 

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

#=============== COLOURS ================#

BOLD	:= \033[1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
CYAN	:= \033[36;1m
RESET	:= \033[0m

