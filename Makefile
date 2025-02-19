CXX = g++
CXXFLAGS = -g -Wall -std=c++11

# List of object files
OBJS = amazon.o mydatastore.o product_parser.o db_parser.o product.o util.o user.o book.o clothing.o movie.o

# Executable target
amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o amazon

# Individual compilation rules
amazon.o: amazon.cpp mydatastore.h product.h db_parser.h product_parser.h util.h
	$(CXX) $(CXXFLAGS) -c amazon.cpp

mydatastore.o: mydatastore.cpp mydatastore.h datastore.h product.h user.h util.h
	$(CXX) $(CXXFLAGS) -c mydatastore.cpp

product_parser.o: product_parser.cpp product_parser.h product.h book.h clothing.h movie.h
	$(CXX) $(CXXFLAGS) -c product_parser.cpp

db_parser.o: db_parser.cpp db_parser.h datastore.h product.h user.h product_parser.h
	$(CXX) $(CXXFLAGS) -c db_parser.cpp

product.o: product.cpp product.h
	$(CXX) $(CXXFLAGS) -c product.cpp

util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) -c util.cpp

user.o: user.cpp user.h
	$(CXX) $(CXXFLAGS) -c user.cpp

book.o: book.cpp book.h product.h
	$(CXX) $(CXXFLAGS) -c book.cpp

clothing.o: clothing.cpp clothing.h product.h
	$(CXX) $(CXXFLAGS) -c clothing.cpp

movie.o: movie.cpp movie.h product.h
	$(CXX) $(CXXFLAGS) -c movie.cpp

# Clean build files
clean:
	rm -f *.o amazon