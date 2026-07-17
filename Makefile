# Makefile to compile our Memory Manager
all:
	gcc main.c memory_manager.c -o my_memory_manager

clean:
	rm -f my_mem_manager