COM=g++
IN=todo.cc
OUT=todo

all: todo

todo: $(IN)
	$(COM) -Wall -Werror -std=c++11 $(IN) -o $(OUT)
