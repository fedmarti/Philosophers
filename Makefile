NAME = philosophers

FLAGS = -pthread -g -Wall -Wextra -Werror

CC = gcc

SRC = philosophers.c \
	is_input_valid.c \
	ft_atoi.c \
	ft_calloc.c \
	philo_logic.c \
	start_philos.c \
	logs.c \
	time/return_time_of_day.c \
	time/time_add.c \
	time/time_recalibrate.c \
	time/time_subtract.c \
	time/timeval_to_usec.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^ 

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

PHONY: all clean fclean re