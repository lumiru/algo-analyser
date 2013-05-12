SUBDIRS=sources

libamalgo: lib/libamalgo
	cd lib/libamalgo; \
	if test ! -e Makefile; then \
		./autogen.sh; \
		./configure; \
	fi; \
	make
