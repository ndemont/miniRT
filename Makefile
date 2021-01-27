SRCS		=	./srcs/main.c \
				./srcs/geometry/geometry.c \
				./srcs/parsing/parsing.c \
				./srcs/parsing/parsing_type.c \
				./srcs/ft_atof.c \
				./srcs/shapes/sphere.c \
				./srcs/shapes/triangle.c \
				./srcs/shapes/square.c \
				./srcs/shapes/cylinder.c \
				./srcs/shapes/plan.c \
			
OBJS		=	${SRCS:.c=.o}
INCLUDES	=	-I./includes -I./libmlx -I./libft/includes
RM			=	rm -f
FLAG_C		=	-Wall -Werror -Wextra -O3 -Ofast
FLAG_MLX	=	-lmlx -lft -framework OpenGL -framework AppKit
NAME		=	minirt
FLAG_LIB	=	-L
PATH_MLX	=	./libmlx
PATH_LIBFT	=	./libft
LIBMLX		=	libmlx.a
LIBFT		=	libft.a

all:		${NAME}
${NAME}:	${OBJS} ${LIBFT}
			make -C ${PATH_LIBFT}
			${CC} ${OBJS} ${INCLUDES} ${FLAG_C} ${FLAG_LIB}${PATH_MLX} ${FLAG_LIB}${PATH_LIBFT} ${FLAG_MLX} -o ${NAME}
.c.o:		
			${CC} ${FLAG_C} ${INCLUDES} -c $< -o ${<:.c=.o}
clean:
			${RM} ${OBJS}
			make clean -C ${PATH_LIBFT}

fclean:		clean
			${RM} ${NAME}
re:			fclean all
.PHONY:		all clean fclean re
