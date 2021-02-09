NAME		= minirt
CLEAR		= \033[2K\c
CC			= cc
RM			= rm -rf
OS			= $(shell uname)

CFLAGS		= -Wall -Werror -Wextra -O3 -Ofast
IFLAGS		= -I${INC_DIR} -I${MLX_DIR} -I${LIBFT_DIR}/includes
LFLAGS		= -L ${MLX_DIR} -lmlx -L ${LIBFT_DIR} -lft -framework OpenGL -framework AppKit

SRCS_DIR	= srcs
INC_DIR		= includes
MLX_DIR		= libmac
LIBFT_DIR	= libft
OBJS_DIR	= objs

INC         = $(shell find ${INC_DIR} -type f -name "*.h")
SRCS 		= $(notdir $(shell find ${SRCS_DIR} -type f -name "*.c"))
OBJS 		= $(addprefix ${OBJS_DIR}/, $(SRCS:.c=.o))
vpath		%.c $(shell find ${SRCS_DIR} -type d)
				
ifeq (${OS}, Linux)
	MLX_DIR = liblinux
	IFLAGS  = -I/usr/include -I${MLX_DIR} -I${INC_DIR} -I${LIBFT_DIR}/includes -D LINUX=1
	LFLAGS  = -L ${MLX_DIR} -lmlx -L ${LIBFT} -lft -L /usr/lib -lXext -lX11 -lm
endif 

all: 		init ${NAME}

init:
			$(shell mkdir -p ${OBJS_DIR})
			${MAKE} --silent -C ${LIBFT_DIR}
			${MAKE} --silent -C ${MLX_DIR}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${IFLAGS} -o $@ $^ ${LFLAGS}

${OBJS_DIR}/%.o:	%.c
			@echo "${CLEAR}"
			@echo "compiling $<\r\c"
			@${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@

clean:
			${RM} ${OBJS_DIR}
			${MAKE} clean --silent -C ${LIBFT_DIR}
			${MAKE} clean --silent -C ${MLX_DIR}

fclean:
			${RM} ${OBJS_DIR}
			${RM} ${NAME}
			${MAKE} fclean --silent -C ${LIBFT_DIR}
			${MAKE} clean --silent -C ${MLX_DIR}

re:			fclean all

norme:
			~/.norminette/norminette.rb ${SRCS_DIR}
			~/.norminette/norminette.rb ${INC_DIR}

.SUFFIXES:	.c .o .h
.PHONY:		all clean fclean re
