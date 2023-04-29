NAME=pac
OBJFILES=main.o pacman.o
LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf
HEADFILES=

CC=gcc
CFLAGS= -fsanitize=address -g

$(NAME): $(OBJFILES) $(HEADFILES) 
	$(CC) $(CFLAGS) $(OBJFILES) -o $@ $(LIBS)

%.o : %.c $(HEADFILES)
	$(CC) $(CFLAGS) -c $<

all: clean $(NAME)

clean_bin:
	rm -f $(NAME)

clean_obj:
	rm -f *.o

clean: clean_bin clean_obj
