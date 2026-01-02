# projekt-setup
TARGET = informer
CC = gcc
# pfade für includes: aktuelles verzeichnis und eins drüber
CFLAGS = -Wall -O2 `pkg-config --cflags glfw3 freetype2 gl` -I. -I..
LIBS = `pkg-config --libs glfw3 freetype2 gl` -lm

# explizite quellen: alles im ordner + die externe renderer-klasse
SRCS = $(wildcard *.c) ../glftRenderString.c
# objekte werden lokal gebaut, damit wir nicht im elternverzeichnis rummüllen
OBJS = informer.o glftRenderString.o

# standard target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBS)

# regeln für die objekte
informer.o: informer.c
	$(CC) $(CFLAGS) -c informer.c -o informer.o

glftRenderString.o: ../glftRenderString.c
	$(CC) $(CFLAGS) -c ../glftRenderString.c -o glftRenderString.o

# ausführen
run: all
	./$(TARGET) "JUNKYARD MODE" 3000 /usr/share/fonts/truetype/dejavu/DejaVuSans.ttf "0.0,1.0,0.5"

# aufräumen
clean:
	rm -f $(TARGET) *.o

# GitHub-Integration
push: clean
	git add .
	git commit --amend --no-edit || git commit -m "update $(TARGET) source"
	git push origin main --force

# falls du mal einen ordner schnell als neues repo brauchst
createrepo:
	gh repo create $(TARGET) --public --source=. --push

.PHONY: all clean run push createrepo
