# -*- coding: utf-8 -*-

# Copyright 2015 Harri Pitkänen (hatapitk@iki.fi)
# Program for removing comments and optionally disabled entries from
# LEXC files.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

import sys
sys.path.append("common")
import fileinput
import generate_lex_common

files = [f for f in sys.argv[1:] if not f.startswith("--")]

OPTIONS = generate_lex_common.get_options()

for line_orig in fileinput.input(files):
	line = generate_lex_common.filterVfstInput(unicode(line_orig, 'UTF-8'), OPTIONS)
	if line is None:
		continue
	print line.encode('UTF-8')
