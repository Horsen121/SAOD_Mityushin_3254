#!/bin/sh
valgrind ./list —tool=memcheck
valgrind ./list —leak-check=full