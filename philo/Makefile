NAME = philo

FLAGS = -pthread -g -Wall -Wextra -Werror

CC = gcc

SRC = philosophers.c \
	data_init.c \
	is_input_valid.c \
	ft_atoi.c \
	ft_calloc.c \
	philo_logic.c \
	start_philos.c \
	logs.c \
	think_state.c \
	eat_state.c \
	sleep_state.c \
	state_machine_utils.c \
	time/return_time_of_day.c \
	time/time_add.c \
	time/time_recalibrate.c \
	time/time_subtract.c \
	time/timeval_to_usec.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $@ $^
	@echo "$(NAME) compiled"

.c.o:
	@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

clean:
	@rm -rf *.o
	@rm -rf time/*.o
	@echo ".o files removed"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(NAME) removed"

re: fclean all

PHONY: all clean fclean re
