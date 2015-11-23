# This file is part of Pendual Enabler.
#
# Copyright (C) 2015  kclkcl
# Copyright (C) 2015  contrixed
#
# Pendual Enabler is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# any later version.
#
# Pendual Enabler is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Pendual Enabler.  If not, see <http://www.gnu.org/licenses/>.

.PHONY: clean unittest

CC=gcc
PI = python
FAKEDLL = fakedll.py
FLAGS= -std=c11 -Wall -pedantic
TARGET = pendual
TARGET_UNITTEST = punittest
SRC_UNITTEST = unittest.c
SRC = $(wildcard src/*.c)
HEADERS = $(wildcard src/inc/*.h)
OBJECTS = $(SRC:.o=.c)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(TARGET)

unittest:
	$(PI) $(FAKEDLL)
	$(CC) $(FLAGS) $(SRC_UNITTEST) -o $(TARGET_UNITTEST)

clean:
	rm -vfr *~ $(TARGET)
	rm -vfr *~ $(TARGET_UNITTEST)
