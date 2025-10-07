CC=gcc
CFLAGS=-c -Wextra
LDFLAGS= -o start.exe -std=c99
SOURCES= main.c vect_math.c vect.c io_helper.c op_helper.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=start.exe

all: $(SOURCES) $(EXECUTABLE) 

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o: 
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

# Preprocess all source files and save output as .i files
preprocess: $(SOURCES:.c=.i)

%.i: %.c
	$(CC) -E $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d *.i
       