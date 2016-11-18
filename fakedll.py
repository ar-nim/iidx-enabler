#!/usr/bin/env python
# -*- coding:utf-8 -*-
#
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

from __future__ import print_function
from __future__ import unicode_literals
import os

'''Provides a method of generating a fake bm2x dll for unittesting
    or debugging purposes. This DLL file is not real, it is just using
    the same values at the same offset as the actual DLL would look like
    in a hex editor.'''

def create_fake_dll():
    '''Create and write the data to the fake DLL file.'''
    print('Creating file "fake.bm2x.dll"\n')
    with open('fake.bm2x.dll', 'w+') as write:
        # Timer freeze.
        write.seek(0x9C55E, os.SEEK_SET)
        write.write(chr(0x74))

        write.seek(0x71182, os.SEEK_SET)
        write.write(chr(0x74))
        write.seek(0x71183, os.SEEK_SET)
        write.write(chr(0x32))

        # All songs unlocked.
        write.seek(0x58B3E, os.SEEK_SET)
        write.write(chr(0x75))
        write.seek(0x58B3F, os.SEEK_SET)
        write.write(chr(0x0A))

        # Song delay.
        write.seek(0x77CF6, os.SEEK_SET)
        write.write(chr(0x7C))

        # premium_free
        write.seek(0x6BF3A, os.SEEK_SET)
        write.write(chr(0x74))
        write.seek(0x6BF3B, os.SEEK_SET)
        write.write(chr(0x23))

        # premium_timer_freeze
        write.seek(0x5D31B, os.SEEK_SET)
        write.write(chr(0x75))

        write.seek(0x563AD, os.SEEK_SET)
        write.write(chr(0x48))

        write.seek(0x14C3A, os.SEEK_SET)
        write.write(chr(0x90))
        write.seek(0x14C3B, os.SEEK_SET)
        write.write(chr(0x3f))
        write.seek(0x14C3C, os.SEEK_SET)
        write.write(chr(0x12))
        write.seek(0x14C3D, os.SEEK_SET)
        write.write(chr(0x10))
        write.seek(0xD5D09, os.SEEK_SET)
        write.write(chr(0xEB) + chr(0x00))
        print('fake.bm2x.dll Created successfully.')

if __name__ == '__main__':
    create_fake_dll()
