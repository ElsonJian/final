
# Makefile for f2022, ecs36b
# https://macappstore.org/libjson-rpc-cpp/
# https://github.com/cinemast/libjson-rpc-cpp

CC = g++ -std=c++14
CFLAGS = -g -I/usr/include/jsoncpp

# LDFLAGS = 	-L/Users/sfwu/vcpkg/installed/arm64-osx/lib -ljsoncpp -L/opt/homebrew/lib/ -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

LDFLAGS = 	-ljsoncpp -L/Users/elson/vcpkg/installed/arm64-osx/lib  -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server -ljsonrpccpp-client -lcurl

INC	=		ecs36b_Common.h
INC_CL	=	person.h vehicle.h motorcycle.h car_general.h
OBJ	=		person.o  motorcycle.o car_general.o #vehicle.o


# rules.
all: 	motorcycle1 motorcycle2 car

#
#
# <target> : [... tab...] <dependency>
# [... tab ....] <action>

finalclient.h:		ecs36b_final.json
	jsonrpcstub ecs36b_final.json --cpp-server=finalserver --cpp-client=finalclient

finalserver.h:		ecs36b_final.json
	jsonrpcstub ecs36b_final.json --cpp-server=finalserver --cpp-client=finalclient

motorcycle1.o:		motorcycle1.cpp finalserver.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) motorcycle1.cpp

motorcycle2.o:		motorcycle2.cpp finalserver.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) motorcycle2.cpp

car.o:		car.cpp finalserver.h $(INC_CL) $(INC)
	$(CC) -c $(CFLAGS) car.cpp

ecs36b_JSON.o:		ecs36b_JSON.cpp $(INC)
	$(CC) -c $(CFLAGS) ecs36b_JSON.cpp

person.o:	person.cpp person.h $(INC)
	$(CC) -c $(CFLAGS) person.cpp

#vehicle.o:	vehicle.cpp vehicle.h $(INC)
#$(CC) -c $(CFLAGS) vehicle.cpp

motorcycle.o:	motorcycle.cpp motorcycle.h $(INC)
	$(CC) -c $(CFLAGS) motorcycle.cpp

car_general.o:	car_general.cpp car_general.h $(INC)
	$(CC) -c $(CFLAGS) car_general.cpp

motorcycle1: motorcycle1.o ecs36b_JSON.o $(OBJ)
	$(CC) -o motorcycle1 motorcycle1.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

motorcycle2: motorcycle2.o ecs36b_JSON.o $(OBJ)
	$(CC) -o motorcycle2 motorcycle2.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

car: car.o ecs36b_JSON.o $(OBJ)
	$(CC) -o car car.o ecs36b_JSON.o $(OBJ) $(LDFLAGS)

clean:
	rm -f *.o finalclient.h finalserver.h motorcycle1 motorcycle2 car