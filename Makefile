NAME = philosophers

FLAGS = -pthreads -g -wall -wextra -werror

CC = gcc

SRC = philosophers.c \
	is_input_valid.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^ 

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)