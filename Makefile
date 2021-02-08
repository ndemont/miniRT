SRCS		=	./srcs/main.c \
				./srcs/geometry/geometry.c \
				./srcs/parsing/parsing.c \
				./srcs/parsing/parsing_shapes.c \
				./srcs/parsing/parsing_env.c \
				./srcs/parsing/parsing_type.c \
				./srcs/ft_atof.c \
				./srcs/shapes/sphere.c \
				./srcs/shapes/triangle.c \
				./srcs/shapes/square.c \
				./srcs/shapes/cylinder.c \
				./srcs/shapes/plan.c \
				./srcs/shapes/intersections.c \
				./srcs/colors/lights.c \
				./srcs/colors/shadows.c \
				./srcs/hooks/hooks.c \
				./srcs/geometry/vectors_op.c \
				./srcs/geometry/vectors_op2.c \
				./srcs/geometry/vectors_tools.c \
				./srcs/bmp/bmp_file.c \
				
OBJS		=	${SRCS:.c=.o}
INCLUDES	=	-I./includes -I./liblinux -I./libft/includes -I/usr/include
RM			=	rm -f
FLAG_C		=	-O3 -Ofast
FLAG_MLX	=	-lmlx -lm -lbsd -lX11 -lXext -lft #:-framework OpenGL -framework AppKit
NAME		=	minirt
FLAG_LIB	=	-L
PATH_MLX	=	./liblinux
PATH_LIBFT	=	./libft
LIBMLX		=	libmlx.a
LIBFT		=	libft.a

all:		${NAME}
${NAME}:	${OBJS} ${LIBFT}
			make -C ${PATH_LIBFT}
			${CC} ${OBJS} ${INCLUDES} ${FLAG_C} -o ${NAME} ${FLAG_LIB}${PATH_MLX} ${FLAG_LIB}${PATH_LIBFT} ${FLAG_MLX} -L /usr/lib
.c.o:		
			${CC} ${FLAG_C} ${INCLUDES} -c $< -o ${<:.c=.o}
clean:
			${RM} ${OBJS}
			make clean -C ${PATH_LIBFT}

fclean:		clean
			${RM} ${NAME}
re:			fclean all
.PHONY:		all clean fclean re
