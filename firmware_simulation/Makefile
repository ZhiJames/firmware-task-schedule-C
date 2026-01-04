CFLAGS = -std=c11 -g -Wall -Wshadow -Wextra -Werror -pedantic -Iinclude
GCC = gcc

SRCS = src/main.c src/ringbuf.c src/scheduler.c
OBJS = $(SRCS:.c=.o)

firmware_sim: $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) -o firmware_sim

run: firmware_sim
	./firmware_sim

src/%.o: src/%.c
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) firmware_sim output*

.PHONY: clean