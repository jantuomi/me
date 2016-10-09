CXX=g++
CXXFLAGS=-std=c++11 -Wall -O2
SRC=*.cpp
TARGET=me
PREFIX=$$PREFIX
all:
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET)  
	echo "Done."

clean: $(TARGET)
	rm $(TARGET)

test:
	echo $(PREFIX)

install: $(TARGET)
	if [ -z "$$PREFIX" ] ; then \
		echo "No PREFIX set. Aborting install."; \
	else \
		echo "Installing in $$PREFIX/bin/..."; \
		cp me "$$PREFIX"/bin/me; \
		if [ $$? -eq 0 ] ; then \
			echo "Installation successful."; \
		else \
			echo "Installation failed."; \
		fi \
	fi	

