CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -I. -Iapp/encryptDecrypt -Iapp/fileHandling -Iapp/processes

MAIN_TARGET = encrypt_decrypt
CRYPTION_TARGET = cryption

MAIN_SRC = main.cpp \
           app/processes/ProcessManagement.cpp \
           app/fileHandling/IO.cpp \
           app/fileHandling/ReadEnv.cpp \
           app/encryptDecrypt/Cryption.cpp

CRYPTION_SRC = app/encryptDecrypt/CryptionMain.cpp \
               app/encryptDecrypt/Cryption.cpp \
               app/fileHandling/IO.cpp \
               app/fileHandling/ReadEnv.cpp

MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
CRYPTION_OBJ = $(CRYPTION_SRC:.cpp=.o)

all: $(MAIN_TARGET) $(CRYPTION_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(CRYPTION_TARGET): $(CRYPTION_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJ) $(CRYPTION_OBJ) $(MAIN_TARGET) $(CRYPTION_TARGET)

.PHONY: clean all
