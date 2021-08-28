CC := gcc
CFLAGS :=

TASK_1 := TCP
TASK_2 := UDP

PROG_1 := client
PROG_2 := server

.PHONY: all $(TASK_1) $(TASK_2) clean

all: $(TASK_1) $(TASK_2)

debug: CFLAGS += -g
debug: all

$(TASK_1): $(TASK_1)/$(PROG_1).c $(TASK_1)/$(PROG_2).c
	$(CC) $(CFLAGS) $(TASK_1)/$(PROG_1).c -o  $(TASK_1)/$(PROG_1)
	$(CC) $(CFLAGS) $(TASK_1)/$(PROG_2).c -o  $(TASK_1)/$(PROG_2)

$(TASK_2): $(TASK_2)/$(PROG_1).c $(TASK_2)/$(PROG_2).c
	$(CC) $(CFLAGS) $(TASK_2)/$(PROG_1).c -o  $(TASK_2)/$(PROG_1)
	$(CC) $(CFLAGS) $(TASK_2)/$(PROG_2).c -o  $(TASK_2)/$(PROG_2)

clean:
	rm -rf $(TASK_1)/$(PROG_1) $(TASK_1)/$(PROG_2) $(TASK_2)/$(PROG_1) $(TASK_2)/$(PROG_2)
