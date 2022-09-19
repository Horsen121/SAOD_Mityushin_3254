#!/bin/sh
valgrind ./task5 —tool=memcheck
valgrind ./task5 —leak-check=full