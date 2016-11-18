# This file is part of IIDX Enabler.
#
# Copyright (C) 2016  kclkcl
# Copyright (C) 2015  contrixed
#
# IIDX Enabler is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# any later version.
#
# IIDX Enabler is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with IIDX Enabler.  If not, see <http://www.gnu.org/licenses/>.

CC=gcc
FLAGS= -std=c11 -Wall -pedantic
TARGET = iidx-enabler
SRC = $(wildcard src/*.c)
HEADERS = $(wildcard src/inc/*.h)
OBJECTS = $(SRC:.o=.c)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(TARGET)

clean:
	rm -vfr *~ $(TARGET)
	rm -vfr *~ $(TARGET_UNITTEST)
