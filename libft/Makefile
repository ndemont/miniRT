SRCS		=	./srcs/gnl/get_next_line.c \
				./srcs/put/ft_putstr_fd.c \
				./srcs/put/ft_putnbr_fd.c \
				./srcs/put/ft_putendl_fd.c \
				./srcs/put/ft_putchar_fd.c \
				./srcs/is/ft_isdigit.c \
				./srcs/is/ft_isascii.c \
				./srcs/is/ft_isprint.c \
				./srcs/is/ft_isalpha.c \
				./srcs/is/ft_isalnum.c \
				./srcs/lst/ft_lstadd_back.c \
				./srcs/lst/ft_lstnew.c \
				./srcs/lst/ft_lstlast.c \
				./srcs/lst/ft_lstclear.c \
				./srcs/lst/ft_lstiter.c \
				./srcs/lst/ft_lstmap.c \
				./srcs/lst/ft_lstsize.c \
				./srcs/lst/ft_lstadd_front.c \
				./srcs/lst/ft_lstdelone.c \
				./srcs/str/ft_strnstr.c \
				./srcs/str/ft_strncpy_bonus.c \
				./srcs/str/ft_strcat_bonus.c \
				./srcs/str/ft_strncat_bonus.c \
				./srcs/str/ft_strcpy_bonus.c \
				./srcs/str/ft_strlcpy.c \
				./srcs/str/ft_strlen.c \
				./srcs/str/ft_strchr.c \
				./srcs/str/ft_strjoin.c \
				./srcs/str/ft_split.c \
				./srcs/str/ft_strrchr.c \
				./srcs/str/ft_substr.c \
				./srcs/str/ft_strncmp.c \
				./srcs/str/ft_strcmp_bonus.c \
				./srcs/str/ft_strmapi.c \
				./srcs/str/ft_strtrim.c \
				./srcs/str/ft_strlcat.c \
				./srcs/str/ft_strdup.c \
				./srcs/mem/ft_memcmp.c \
				./srcs/mem/ft_bzero.c \
				./srcs/mem/ft_memcpy.c \
				./srcs/mem/ft_memccpy.c \
				./srcs/mem/ft_memchr.c \
				./srcs/mem/ft_memset.c \
				./srcs/mem/ft_memmove.c \
				./srcs/mem/ft_calloc.c \
				./srcs/convert/ft_toupper.c \
				./srcs/convert/ft_atoi.c \
				./srcs/convert/ft_atof.c \
				./srcs/convert/ft_itoa.c \
				./srcs/convert/ft_tolower.c \
				./srcs/printf/ft_put_functions.c \
				./srcs/printf/ft_printf.c \
				./srcs/printf/ft_create_parsing.c \
				./srcs/printf/ft_print_chars.c \
				./srcs/printf/ft_print_integer.c \
				./srcs/printf/ft_check_parsing.c \
				./srcs/printf/ft_check_conversion.c \
				./srcs/printf/ft_init_parsing.c \
				./srcs/printf/ft_print_hexa.c \
				./srcs/printf/ft_select_conversion.c \

OBJS		=	${SRCS:.c=.o}
INCLUDES	=	./includes
NAME		=	libft.a
CC			=	clang
RM 			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror

COLOR_DEFAULT	= \e[0m
COLOR_GREEN		= \e[92m
COLOR_YELLOW	= \e[93m
COLOR_BLUE		= \e[94m
CLEAR			= \033[2K

all:		${NAME}
	
${NAME}:	${OBJS} ${INCLUDES}
			@printf "${CLEAR}"
			@ar rcs ${NAME} ${OBJS}
			@printf "📚 ${COLOR_BLUE}${NAME} created${COLOR_DEFAULT}\n"

.c.o:
			@printf "${CLEAR}"
			@printf "🚧 ${COLOR_GREEN}Compiling $<${COLOR_DEFAULT}\r"
			@${CC} ${CFLAGS} -I${INCLUDES} -c $< -o ${<:.c=.o}
clean:
			@printf "🧽 ${COLOR_YELLOW}Cleaning... ${NAME}${COLOR_DEFAULT}\n"
			@${RM} ${OBJS} ${OBJS_B}

fclean:		clean
			@printf "🧼 ${COLOR_YELLOW}Deep Cleaning... ${NAME}${COLOR_DEFAULT}\n"
			@${RM} ${NAME}


re:			fclean all

.PHONY:		all clean fclean re bonus
