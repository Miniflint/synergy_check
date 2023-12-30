FILES = ./main.c ./tries.c ./utils.c

CC = gcc

ifeq ($(DEBUG), debug)
	DEBUGCC = -fsanitize=address -g3
endif

all:
	$(CC) $(DEBUGCC) -g $(FILES) -o champ_synergies

build:
	docker build -t arch -f ./outfiles/Dockerfile .
	docker run -v .:/checking_files -ti arch

rundock:
	docker run -v .:/checking_files -ti arch

prune:
	docker system prune -a --volumes