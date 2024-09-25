########################################################################################################################
#                                                       VARIABLE                                                       #
########################################################################################################################
SRCS		:=	main.c\
				init.c\
				destroy.c\
				utils.c\
				fork.c\
				eat.c\
				routine.c\
				write.c

HEAD		:=	philo.h
HEAD_D		:=	./inc/
HEAD_A		:=	$(addprefix $(HEAD_D), $(HEAD))

SRCS_D		:=	srcs/

OBJS_D		:=	.objs/
OBJS		=	$(SRCS:%.c=$(OBJS_D)%.o)

NAME		:=	philo
########################################################################################################################
#                                                        FLAGS                                                         #
########################################################################################################################

RM		:=	rm -rf
# -Wall -Wextra -Werror
CC		:=	cc
# -fsanitize=address
CFLAGS	:= -Wall -Wextra -Werror -Ofast -I$(HEAD_D)

all			:	$(NAME)

$(NAME)		:	$(OBJS_D) $(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

$(OBJS)		:	$(OBJS_D)%.o: $(SRCS_D)%.c $(HEAD_A)
				$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_D)	:
				mkdir -p $(OBJS_D)

clean		:
				$(RM) $(OBJS) $(OBJS_D)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re
