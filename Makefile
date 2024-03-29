CC = gcc
CFLAGS = -Wall -g
SRCDIR = src
OBJDIR = obj
LIBDIR = lib
BINDIR = bin
DOCDIR = doc
SDL_DIR = ${HOME}/SDL2
SDLLIB_DIR = ${SDL_DIR}/lib
SDLINC_DIR = ${SDL_DIR}/include

# List all the source files in SRCDIR with a .c extension
SOURCES = $(wildcard $(SRCDIR)/*.c)
# Derive the object file names from the source file names
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
# Derive the dependency file names from the object file names
DEPS = $(OBJECTS:.o=.d)

# Set the flags to include the SDL header files and libraries
INCLUDES = -I${SDLINC_DIR}
LIBS = -L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lm

# The final executable name
EXEC = pingouin_bros

# Create the directories for object files and executables
$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)
$(DOCDIR):
	mkdir -p $(DOCDIR)

# The all target builds the executable
all: $(BINDIR)/$(EXEC)

# Link the object files to create the executable
$(BINDIR)/$(EXEC): $(OBJECTS) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $@

# Compile each source file into an object file
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Include the dependency files generated by the compiler
-include $(DEPS)

# Clean up the object files and executable
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Clean up the object files, executable, and documentation
mrproper: clean
	rm -rf $(DOCDIR)

# Generate the documentation using Doxygen
doxygen:
	doxygen

# Open the index.html file in the doc/html directory
docs: doxygen | $(DOCDIR)
	open $(DOCDIR)/html/index.html
