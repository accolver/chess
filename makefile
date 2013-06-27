################################################################################
# CS 240 Chess Project Makefile
# 
# Last Modified: 21 April 2011 by Wayne Robison 
#
# INSTRUCTIONS: This is a starting makefile for the chess project. You are to 
# keep this up-to-date as you add source files. In addition to keeping it 
# up-to-date with new files you create, you need to make the following changes 
# to this makefile:
# 
#	- compile the object files associated with the View into a shared library, 
#	- add pseudo-targets for the different run modes (namely "runhh", "runhc",
#		"runch", and "runcc"),
#	- add a "test" pseudo-target (you will probably want to make a new executable
#		for this with its own main method),
#	- add a "lib" pseudo-target,
#	- edit the command associated with the memcheck pseudo-target (i.e.,
#		the valgrind command. See the note above it for details).
# 
# NOTES: 
# 1. All the code for the GUI side of this project is provided for you. As a 
# result, there are some things in this makefile which you do not need to alter.
# Such items will be clearly marked with comments.
# 2. Out-of-the-box, without making any changes to this initial makefile, 
# running "make run" will compile the code and bring up an empty GUI. 
################################################################################

 
############### --- BEGIN UNTOUCHABLE SECTION - Do Not Edit --- ################
# Macros for GUI libraries.
GTKMM = gtkmm-2.4
SIGC = sigc++-2.0
LIBGLADE = libglademm-2.4

# TODO Re-phrase: CFLAGS are the -I values needed to compile files using the 
# GTKMM, SIGC, and LIBGLADE libraries
CFLAGS = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --cflags`
# TODO Re-phrase: LIBS are the paths to the static libraries for GTKMM, SIGC,
# and LIBGLADE needed for linking
LIBS   = `pkg-config $(GTKMM) $(SIGC) $(LIBGLADE) --libs`
####################### --- END UNTOUCHABLE SECTION --- ########################


# TODO Re-phrase: Macros for directory tree locations
MODEL_SRC = model/src/
MODEL_INC = model/inc/
MODEL_OBJ = model/obj/
VIEW_SRC = view/src/
VIEW_INC = view/inc/
VIEW_OBJ = view/obj/
CONT_SRC = controller/src/
CONT_INC = controller/inc/
CONT_OBJ = controller/obj/
UTIL_INC = utils/inc/
UTIL_SRC = utils/src/
UTIL_OBJ = utils/obj/
EXE = bin/chess			# normal executable
TEXE = bin/test
MEXE = bin/mchess			# executable for memory testing

# Macros for compilation flags
INCLUDES = -I$(MODEL_INC) -I$(VIEW_INC) -I$(CONT_INC) -I$(UTIL_INC)
DEBUG = -g# Uncomment this if you want to compile with debug info

# Uncomment the flag on this next line to turn off the logging messages from the
# GUI
LOG_FLAG = '-DLOG_LEVEL_HIDE_MASK=(G_LOG_LEVEL_DEBUG|G_LOG_LEVEL_INFO)'


# There are two different main.o files. One is for memory testing.
MAIN_O = $(CONT_OBJ)main.o
TEST_O = $(CONT_OBJ)test.o
MEMMAIN_O = $(CONT_OBJ)memcheck_main.o

# This macro should be used to store all of the object files created 
# from *your* source files
MY_OBJS = $(MODEL_OBJ)Board.o \
	  $(MODEL_OBJ)ChessGame.o \
	  $(MODEL_OBJ)Move.o \
	  $(MODEL_OBJ)Piece.o \
	  $(MODEL_OBJ)Position.o \
	  $(MODEL_OBJ)XMLReader.o \
	  $(MODEL_OBJ)XMLWriter.o \
	  $(MODEL_OBJ)King.o \
	  $(MODEL_OBJ)Queen.o \
	  $(MODEL_OBJ)Rook.o \
	  $(MODEL_OBJ)Bishop.o \
	  $(MODEL_OBJ)Knight.o \
	  $(MODEL_OBJ)Pawn.o \
	  $(CONT_OBJ)ComputerPlayer.o \
	  $(CONT_OBJ)HumanPlayer.o \
	  $(CONT_OBJ)ChessController.o \
	  $(UTIL_OBJ)HTMLToken.o \
	  $(UTIL_OBJ)HTMLTokenizer.o \
	  $(UTIL_OBJ)StringUtil.o \
		

# These are all the object files that go into the library
LIB_OBJS = $(VIEW_OBJ)ChessView.o \
      $(VIEW_OBJ)ChessGuiBoardCell.o \
      $(VIEW_OBJ)ChessGuiBoard.o \
      $(VIEW_OBJ)ChessGui.o \
      $(VIEW_OBJ)ChessGuiImages.o \
      $(VIEW_OBJ)SelectDialog.o


DLL = lib/libcs240utils.so


################################################################################
# Pseudo-targets
runhh: $(EXE)
	$(EXE) 0
runhc: $(EXE)
	$(EXE) 1
runch: $(EXE)
	$(EXE) 2
runcc: $(EXE)
	$(EXE) 3
run: $(EXE)
	$(EXE)
test: $(TEXE)
	$(TEXE)

bin: $(EXE)

lib: $(DLL)

# Run the executable for memory testing
# Instructions: Edit the command below so that it runs the  
# memory-check executable in Human-Human mode (i.e., add necessary command  
# line arguments to the end of valgrind the command below).	
memcheck: $(MEXE)
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=string.supp $(MEXE) 0 #command-line args go here

# Clean removes all of the .o files, libraries, and executables
clean:
	@rm -f $(MODEL_OBJ)*.o
	@rm -f $(VIEW_OBJ)*.o
	@rm -f $(CONT_OBJ)*.o
	@rm -f lib/*.so
	@rm -f $(EXE)
	@rm -f $(MEXE)
	@rm -f $(TEXE)


################################################################################
# Targets for executables and main object files

# Explanation: There are two different executables, with two different main 
# object files, because main.cpp needs to be built differently depending on 
# whether you are doing memory testing or not. This is because the GTK library,
# and other GUI tools, have memory leaks that we cannot figure out how to 
# suppress. Therefore, when building an executable for memory testing, we use a
# macro (MEMCHECK) to tell the compiler to not include the code that builds the
# GUI. So when we check for memory leaks during passoff, we don't have to use
# the GUI.

# Main executable
# Note: Once you have added the ability to make a library out of the View files, 
# the executable should be dependent on, and link in the library file, not the 
# .o files! That means, instead of linking in $(LIB_OBJS) below, you should link
# in the actual library file.
$(EXE): $(MAIN_O) $(MY_OBJS) $(DLL)
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(INCLUDES) -o $(EXE) $(MAIN_O) $(MY_OBJS) $(DLL) $(CFLAGS) $(LIBS)
	chmod ugo+x $(EXE)

$(TEXE): $(TEST_O) $(MY_OBJS) $(DLL)
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(INCLUDES) -o $(TEXE) $(TEST_O) $(MY_OBJS) $(DLL) $(CFLAGS) $(LIBS)
	chmod ugo+x $(TEXE)

# Executable for memory testing
$(MEXE): $(MEMMAIN_O) $(MY_OBJS) $(DLL)
	@# Re-link executable. Again, this should link the library file, not the .o's
	g++ $(INCLUDES) -o $(MEXE) $(MEMMAIN_O) $(MY_OBJS) $(DLL) $(CFLAGS) $(LIBS)
	chmod ugo+x $(MEXE)
	

# Main object file
$(MAIN_O): $(CONT_SRC)main.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)ChessView.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MAIN_O) -c $(LOG_FLAG) $(CONT_SRC)main.cpp

$(TEST_O): $(CONT_SRC)test.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)ChessView.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(TEST_O) -c $(LOG_FLAG) $(CONT_SRC)test.cpp

# Main .o for memory testing
$(MEMMAIN_O): $(CONT_SRC)main.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)ChessView.h
	g++ -DMEMCHECK $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(MEMMAIN_O) -c $(LOG_FLAG) $(CONT_SRC)main.cpp


$(DLL): $(LIB_OBJS)
	g++ -shared -o $(DLL) $(VIEW_OBJ)*.o
	

################################################################################
# Targets for YOUR object files...

$(MODEL_OBJ)Board.o : $(MODEL_SRC)Board.cpp $(MODEL_INC)Board.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)Board.o $(INCLUDES) $(MODEL_SRC)Board.cpp
$(MODEL_OBJ)ChessGame.o : $(MODEL_SRC)ChessGame.cpp $(MODEL_INC)ChessGame.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)ChessGame.o $(INCLUDES) $(CFLAGS) $(MODEL_SRC)ChessGame.cpp
$(MODEL_OBJ)Move.o : $(MODEL_SRC)Move.cpp $(MODEL_INC)Move.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)Move.o $(INCLUDES) $(MODEL_SRC)Move.cpp
$(MODEL_OBJ)Position.o : $(MODEL_SRC)Position.cpp $(MODEL_INC)Position.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)Position.o $(INCLUDES) $(MODEL_SRC)Position.cpp
$(MODEL_OBJ)XMLReader.o : $(MODEL_SRC)XMLReader.cpp $(MODEL_INC)XMLReader.h $(UTIL_OBJ)HTMLToken.o $(UTIL_INC)HTMLToken.h $(UTIL_OBJ)HTMLTokenizer.o $(UTIL_INC)HTMLTokenizer.h $(UTIL_OBJ)StringUtil.o $(UTIL_INC)StringUtil.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)XMLReader.o $(INCLUDES) $(MODEL_SRC)XMLReader.cpp
$(MODEL_OBJ)XMLWriter.o : $(MODEL_SRC)XMLWriter.cpp $(MODEL_INC)XMLWriter.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)XMLWriter.o $(INCLUDES) $(MODEL_SRC)XMLWriter.cpp

$(MODEL_OBJ)Piece.o : $(MODEL_SRC)Piece.cpp $(MODEL_INC)Piece.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)Piece.o $(INCLUDES) $(MODEL_SRC)Piece.cpp
$(MODEL_OBJ)King.o : $(MODEL_SRC)King.cpp $(MODEL_INC)King.h $(MODEL_INC)Piece.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)King.o $(INCLUDES) $(MODEL_SRC)King.cpp
$(MODEL_OBJ)Queen.o : $(MODEL_SRC)Queen.cpp $(MODEL_INC)Queen.h $(MODEL_INC)Piece.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)Queen.o $(INCLUDES) $(MODEL_SRC)Queen.cpp
$(MODEL_OBJ)Rook.o : $(MODEL_SRC)Rook.cpp $(MODEL_INC)Rook.h $(MODEL_INC)Piece.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)Rook.o $(INCLUDES) $(MODEL_SRC)Rook.cpp
$(MODEL_OBJ)Bishop.o : $(MODEL_SRC)Bishop.cpp $(MODEL_INC)Bishop.h $(MODEL_INC)Piece.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)Bishop.o $(INCLUDES) $(MODEL_SRC)Bishop.cpp
$(MODEL_OBJ)Knight.o : $(MODEL_SRC)Knight.cpp $(MODEL_INC)Knight.h $(MODEL_INC)Piece.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)Knight.o $(INCLUDES) $(MODEL_SRC)Knight.cpp
$(MODEL_OBJ)Pawn.o : $(MODEL_SRC)Pawn.cpp $(MODEL_INC)Pawn.h $(MODEL_INC)Piece.h
	g++ -c $(DEBUG) -o $(MODEL_OBJ)Pawn.o $(INCLUDES) $(MODEL_SRC)Pawn.cpp

$(UTIL_OBJ)HTMLToken.o : $(UTIL_SRC)HTMLToken.cpp $(UTIL_INC)HTMLToken.h
	g++ -c $(DEBUG) -o $(UTIL_OBJ)HTMLToken.o $(INCLUDES) $(UTIL_SRC)HTMLToken.cpp
$(UTIL_OBJ)HTMLTokenizer.o : $(UTIL_SRC)HTMLTokenizer.cpp $(UTIL_INC)HTMLTokenizer.h
	g++ -c $(DEBUG) -o $(UTIL_OBJ)HTMLTokenizer.o $(INCLUDES) $(UTIL_SRC)HTMLTokenizer.cpp
$(UTIL_OBJ)StringUtil.o : $(UTIL_SRC)StringUtil.cpp $(UTIL_INC)StringUtil.h
	g++ -c $(DEBUG) -o $(UTIL_OBJ)StringUtil.o $(INCLUDES) $(UTIL_SRC)StringUtil.cpp


$(CONT_OBJ)ChessController.o : $(CONT_SRC)ChessController.cpp $(CONT_INC)ChessController.h
	g++ -c $(DEBUG) -o $(CONT_OBJ)ChessController.o $(INCLUDES) $(CFLAGS) $(CONT_SRC)ChessController.cpp
$(CONT_OBJ)ComputerPlayer.o : $(CONT_SRC)ComputerPlayer.cpp $(CONT_INC)ComputerPlayer.h
	g++ -c $(DEBUG) -o $(CONT_OBJ)ComputerPlayer.o $(INCLUDES) $(CFLAGS) $(CONT_SRC)ComputerPlayer.cpp
$(CONT_OBJ)HumanPlayer.o :  $(CONT_SRC)HumanPlayer.cpp $(CONT_INC)HumanPlayer.h
	g++ -c $(DEBUG) -o $(CONT_OBJ)HumanPlayer.o $(INCLUDES) $(CFLAGS) $(CONT_SRC)HumanPlayer.cpp

################################################################################
# Targets for GUI-related object files
# Instructions: These will have to be recompiled as position-independent code, 
# so that they can be put into a shared library.

$(VIEW_OBJ)ChessView.o: $(VIEW_SRC)ChessView.cpp $(VIEW_INC)SelectDialog.h $(VIEW_INC)ChessView.h $(CONT_INC)IChessController.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessView.o -c $(LOG_FLAG) -fPIC $(VIEW_SRC)ChessView.cpp

$(VIEW_OBJ)ChessGuiBoardCell.o: $(VIEW_SRC)ChessGuiBoardCell.cpp $(VIEW_INC)ChessGuiBoardCell.h $(VIEW_INC)ChessGuiImages.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiBoardCell.o -c -fPIC $(VIEW_SRC)ChessGuiBoardCell.cpp

$(VIEW_OBJ)ChessGuiBoard.o: $(VIEW_SRC)ChessGuiBoard.cpp $(VIEW_INC)ChessGuiBoard.h $(VIEW_INC)ChessGui.h $(VIEW_INC)ChessGuiImages.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiBoard.o -c -fPIC $(VIEW_SRC)ChessGuiBoard.cpp

$(VIEW_OBJ)ChessGui.o: $(VIEW_SRC)ChessGui.cpp $(VIEW_INC)ChessGui.h $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)SelectDialog.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGui.o -c -fPIC $(VIEW_SRC)ChessGui.cpp

$(VIEW_OBJ)ChessGuiImages.o: $(VIEW_SRC)ChessGuiImages.cpp $(VIEW_INC)ChessGuiImages.h $(VIEW_INC)Inline.h
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)ChessGuiImages.o -c -fPIC $(VIEW_SRC)ChessGuiImages.cpp

$(VIEW_OBJ)SelectDialog.o: $(VIEW_SRC)SelectDialog.cpp
	g++ $(DEBUG) $(INCLUDES) $(CFLAGS) $(LIBS) -o $(VIEW_OBJ)SelectDialog.o -c -fPIC $(VIEW_SRC)SelectDialog.cpp


