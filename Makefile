SRCS		=	./srcs/main.c \
				./srcs/geometry.c
OBJS		=	${SRCS:.c=.o}
INCLUDES	=	-I./includes/ -I./libmlx
RM			=	rm -f
FLAGSC		=	-Wall -Werror -Wextra
FLAGSB		=	-lmlx -framework OpenGL -framework AppKit
NAME		=	minirt
LIBRAIRY	=	-L./libmlx

all:		${NAME}
${NAME}:	${OBJS}
			${CC} ${OBJS} ${INCLUDES} ${FLAGSC} ${LIBRAIRY} ${FLAGSB} -o ${NAME}
.c.o:		
			${CC} ${FLAGSC} ${INCLUDES} -c $< -o ${<:.c=.o}
clean:
			${RM} ${OBJS}
fclean:		clean
			${RM} ${NAME}
re:			fclean all
.PHONY:		all clean fclean re