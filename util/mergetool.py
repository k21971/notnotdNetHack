#!/usr/bin/env python3
# -*- mode: python; indent-tabs-mode: nil; -*-
# SPDX-FileCopyrightText: 2026 Ron Nazarov
# SPDX-License-Identifier: NGPL OR GPL-2.0-or-later
import sys
from enum import Enum


class Status(Enum):
    BOTH = 0
    OLD = 1
    NEW = 2


valid_arguments = ["merge-identical", "extract-old", "extract-new"]

if len(sys.argv) <= 1 or sys.argv[1] not in valid_arguments:
    print(f"Usage: {sys.argv[0]} [{'|'.join(valid_arguments)}]", file=sys.stderr)
    sys.exit(1)

status = Status.BOTH
old_segment = ""
old_segment_start = ""
new_segment = ""
new_segment_start = ""

for line in sys.stdin:
    if line.startswith("<<<<<<<"):
        old_segment = ""
        old_segment_start = line
        status = Status.OLD
    elif line.rstrip() == "=======" and status == Status.OLD:
        new_segment = ""
        new_segment_start = line
        status = Status.NEW
    elif line.startswith(">>>>>>>") and status == Status.NEW:
        if sys.argv[1] == "merge-identical":
            if new_segment == old_segment:
                print(new_segment, end='')
            else:
                print(f"{old_segment_start}{old_segment}{new_segment_start}{new_segment}{line}", end='')
        elif sys.argv[1] == "extract-old":
            print(old_segment, end='')
        elif sys.argv[1] == "extract-new":
            print(new_segment, end='')
        status = Status.BOTH
    elif status == Status.OLD:
        old_segment += line
    elif status == Status.NEW:
        new_segment += line
    elif status == Status.BOTH:
        print(line, end='')
