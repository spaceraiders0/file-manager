install:
	echo Compiling source..
	gcc src/launcher.c -lncurses  \
		src/array/array.h 		  \
		src/workspace/workspace.c \
		src/workspace/workspace.h \
		src/path/path.c			  \
		src/path/path.h			  \
		src/utilities/utilities.c \
		src/utilities/utilities.h
	echo Compilation completed.
