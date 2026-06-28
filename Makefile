CC = gcc

CFLAGS = -Wall -Wextra -I. -Icommon -Itcp -Ithread -Iclient -Iserver -g
LDFLAGS = -pthread

CLIENT_BIN = client_app
SERVER_BIN = server_app

CLIENT_SRCS = client/Client.c \
              client/main.c \
              tcp/TCPSocket.c \
              thread/MThread.c

SERVER_SRCS = server/Server.c \
              server/main.c \
              tcp/TCPSocket.c \
              thread/MThread.c

CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

.PHONY: all clean

all: $(CLIENT_BIN) $(SERVER_BIN)

$(CLIENT_BIN): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(SERVER_BIN): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS) $(CLIENT_BIN) $(SERVER_BIN)