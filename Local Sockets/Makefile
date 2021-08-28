CC := gcc
CFLAGS :=

TASK_1 := TCP

PROG_1 := local_client
PROG_2 := local_server

.PHONY: all $(TASK_1) clean

all: $(TASK_1)

debug: CFLAGS += -g
debug: all

$(TASK_1): $(TASK_1)/$(PROG_1).c $(TASK_1)/$(PROG_2).c
	$(CC) $(CFLAGS) $(TASK_1)/$(PROG_1).c -o  $(TASK_1)/$(PROG_1)
	$(CC) $(CFLAGS) $(TASK_1)/$(PROG_2).c -o  $(TASK_1)/$(PROG_2)

clean:
	rm -rf $(TASK_1)/$(PROG_1) $(TASK_1)/$(PROG_2)
