CC := gcc
CFLAGS :=

TASK_1 := Local\ Sockets/
TASK_2 := Network\ Sockets/

.PHONY: all $(TASK_1) $(TASK_2) clean

all: $(TASK_1) $(TASK_2)

$(TASK_1):
	cd $(TASK_1) && make

$(TASK_2):
	cd $(TASK_2) && make

clean:
	cd $(TASK_1) && make clean
	cd $(TASK_2) && make clean
