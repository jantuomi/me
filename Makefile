PREFIX=$(PREFIX)
all:
	g++ -std=c++11 *.cpp -o me -Wall -O2

clean: me
	rm 'me'

test:
	echo $$PREFIX

install: me
	if [ -z "$$PREFIX" ] ; then \
		echo "No PREFIX set. Aborting install."; \
	else \
		echo "Installing in $$PREFIX/bin/..."; \
		cp me "$$PREFIX"/bin/me; \
		echo "Done."; \
	fi	

