CC           = gcc

CFLAGS       = -Wall -g 
SUBDIRS      = lib test
SRCDIR=src
OBJDIR=obj
BINDIR=bin
DOCDIR=doc
TESTDIR =test

default: all
EXEC =Prog
TEST=test

DIRS=$(OBJDIR) $(BINDIR)


$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(DOCDIR):
	mkdir -p $(DOCDIR)

.PHONY=DIRS

SOURCES = $(wildcard $(SRCDIR)/*.c)
INCLUDES = $(wildcard $(SRCDIR)/*.h)

OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)



$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -c $< -I$(SRCDIR) -o $@
	@echo "Compilation de "$<" terminée!"

$(BINDIR)/$(EXEC):$(OBJECTS)
	@echo $(OBJECTS)
	$(CC) $(OBJECTS) -o $@


all: $(DIRS) $(BINDIR)/$(EXEC) 

.PHONY: clean
clean:
	-rm -rf $(OBJDIR)
	@echo "Nettoyage terminé!"

.PHONY: mrproper
mrproper:  
	-rm -rf $(BINDIR)
	-rm -rf doc/
	@echo "Exécutable et documentation supprimés!"

.PHONY: docs
doxygen:
	doxygen -g
docs:
	#mkdir -p doc : paramétrer doxyfile pour envoyer les fichiers de sortie dans le rep doc
	doxygen Doxyfile
	#open doc/html/index.html