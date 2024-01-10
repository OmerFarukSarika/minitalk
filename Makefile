NAME = minitalk
SERVER = server.c
SERVER_BONUS = server_bonus.c
SERVER_NAME = server
CLIENT = client.c
CLIENT_BONUS = client_bonus.c
CLIENT_NAME = client
UTILS = utils.c
UTILS_BONUS = utils_bonus.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER) $(UTILS)
	@$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_NAME): $(CLIENT) $(UTILS)
	@$(CC) $(CFLAGS) $^ -o $@

bonus: $(SERVER_NAME)_bonus $(CLIENT_NAME)_bonus

$(SERVER_NAME)_bonus: $(SERVER_BONUS) $(UTILS_BONUS)
	@$(CC) $(CFLAGS) $^ -o $@

$(CLIENT_NAME)_bonus: $(CLIENT_BONUS) $(UTILS_BONUS)
	@$(CC) $(CFLAGS) $^ -o $@

clean:
	@rm -rf $(SERVER_NAME) $(CLIENT_NAME) $(SERVER_NAME)_bonus $(CLIENT_NAME)_bonus

fclean: clean

re: fclean all

.PHONY: all clean re bonus
