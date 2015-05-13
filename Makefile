##############################################################################
########################## M A K E F I L E ###################################
##############################################################################
#### Date: 3-15-2015                                               ###########
#### Course: CS 5201, Price                                        ###########
#### Author: Rob Wiehage      Adopted by: Patrick Sullivan         ###########
#### File: Makefile                                                ###########
##############################################################################
# This is a makefile for building assignment 4 driver executable   ###########
##############################################################################

.PHONY: all clean reset redo

########## G + +   C O M M A N D   S E T U P ###############

# CXX = /usr/bin/g++
CXX = g++
CXXFLAGS = -g -Wall -W -pedantic-errors -std=c++11

########## O B J E C T   F I L E S ##############
# The following 2 lines only work with gnu make.
# It's much nicer than having to list them out,
# and less error prone.
SOURCESCPP = $(wildcard *.cpp)
SOURCESHPP = $(wildcard *.hpp)
HEADERS = $(wildcard *.h)

# With Sun's make it has to be done like this, instead of
# using wildcards.
# Well, I haven't figured out another way yet.
#SOURCES = signal.cpp tokentype.cpp token.cpp tokenlist.cpp driver.cpp
#HEADERS = signal.h tokentype.h token.h tokenlist.h

# Looks like it can be done like this, but won't work for gmake.
#SOURCES:sh = ls *.cpp
#HEADERS:sh = ls *.h

OBJECTS = $(SOURCESCPP:%.cpp=%.o)
LINKS = $(SOURCESHPP:%.hpp)

####### M A K E   C O M M A N D S #########

default: driver

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

driver: $(OBJECTS) $(SOURCESHPP) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@
	@echo "Everything worked :-) "

########## A R G   C O M M A N D ##########
clean:
	@rm -f core
	@rm -f driver
	@rm -f .depend
	@rm -f driver.exe
	@rm -f $(OBJECTS)
	@echo "cleaned!"

reset: clean

redo: clean default

########## G E N   D E P E N D E N C I E S ##########
depend:
	@echo "Generating dependencies..."
	@$(CXX) -MM *.cpp > .depend

-include .depend
# Put a dash in front of include when using gnu make.
# It stops gmake from warning us that the file
# doesn't exist yet, even though it will be properly
# made and included when all is said and done.
