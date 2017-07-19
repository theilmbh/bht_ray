CC = g++
CFLAGS = -g -DGL_GLEXT_PROTOTYPES
INCFLAGS = -I./glm-0.9.2.7 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -lfreeimage

RM = /bin/rm -f
all: raytrace
raytrace: main.o camera.o globals.h Primitive.h RayTracer.o RayTracer.h Scene.h Sphere.h Scene.o Primitive.o
	$(CC) $(CFLAGS) -o raytrace main.o camera.o RayTracer.o Scene.o Primitive.o $(INCFLAGS) $(LDFLAGS)
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
camera.o: camera.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c camera.cpp
RayTracer.o: RayTracer.cpp RayTracer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c  RayTracer.cpp
Scene.o: Scene.cpp Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c  Scene.cpp
Primitive.o: Primitive.cpp Primitive.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c  Primitive.cpp
clean:
	$(RM) *.o raytrace *.png
