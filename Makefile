CFLAGS=-g -I include/ -Wall -ansi -pedantic -static -Werror
OBJ=misc.o List.o NeuralNet.o SigmoidNeuron.o
LIBFLAGS=-lm
OUTPUT=nn

default: nn

%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

nn: $(OBJ)
	$(CC) -o $(OUTPUT) $^ $(CFLAGS) $(LIBFLAGS)

clean:
	-rm -f $(OBJ)
	-rm -f $(OUTPUT)