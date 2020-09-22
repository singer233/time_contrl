CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -g -fsanitize=address -D DEBUG
LDFLAGS =  -fsanitize=address

SRC_S = a_socket.cc deamonize.cc error_loger.cc main_server.cc
SRC_C = a_socket.cc error_loger.cc main_client.cc
OBJ_S = $(SRC_S:.cc=.o)
OBJ_C = $(SRC_C:.cc=.o)
EXEC_S = main_server
EXEC_C = client

server: $(EXEC_S)

$(EXEC_S): $(OBJ_S)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ_S) $(LBLIBS)
	mv ${EXEC_S} output/${EXEC_S}
client: $(EXEC_C)

${EXEC_C}: ${OBJ_C}
	$(CXX) $(LDFLAGS) -o $@ $(OBJ_C) $(LBLIBS)
	mv ${EXEC_C} output/${EXEC_C}
clean:
	rm -rf $(OBJ_C) $(EXEC_C) $(OBJ_S) $(EXEC_S) 