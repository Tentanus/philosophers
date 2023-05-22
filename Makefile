# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mweverli <mweverli@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/01 17:54:19 by mweverli      #+#    #+#                  #
#    Updated: 2023/05/22 20:38:00 by mweverli      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#========================================#
#=========  GENERAL VARIABLES:  =========#
#========================================#

NAME		:=	philo

OBJ_DIR		:=	OBJ
SRC_DIR		:=	src
INC_DIR		:=	include
LIB_DIR		:=	lib

SRC			:=	philo.c \
				philo_error.c \
				philo_init.c \
				philo_utils.c

SRC			:=	$(SRC:%.c=$(SRC_DIR)/philo/%.c)
OBJ			:=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEP			:=	$(OBJ:.o=.d)
DIR_LIST	:=	$(sort $(dir $(OBJ)))

-include $(DEP)

#============= COMPILATION ==============#

INCLUDE		:=	-I $(INC_DIR)
LIBRARY		:=	-lpthread

CC			:=	gcc
CFL			:=	-Wall -Werror -Wextra

ifdef DEBUG
CFL			+=	-g
endif

ifdef FSAN
CFL			+=	-fsanitize=thread
endif

COMPILE		:=	$(CC) $(CFL)

#========================================#
#============== RECIPIES  ===============#
#========================================#

var:
	@echo $(SRC) 
	@echo "" 
	@echo $(OBJ) 
	@echo "" 

all: $(DIR_LIST) $(NAME)

$(DIR_LIST):
	@mkdir -p $@

$(NAME): $(OBJ)
	@echo ""
	@$(COMPILE) $(INCLUDE) $(LIBRARY) $(OBJ) -o $(NAME)
	@echo "$(RED)$(COMPILE)$(RESET) $(CYAN)$(INCLUDE)$(RESET) $(LIBRARY) $(GREEN)$(OBJ)$(RESET) -o $(NAME)"

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(COMPILE) $(INCLUDE) -MMD -o $@ -c $< 
	@echo "$(CYAN)COMPILE	$(CFL)	$(notdir $<)$(RESET)"

debug:
	@$(MAKE) DEBUG=1 all

rebug: debug

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)$(BOLD)CLEANING $(NAME)$(RESET)"

fclean: clean 
	@rm -f $(NAME)

re: fclean all

#========================================#
#============== LIBRARIES ===============#
#========================================#


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

