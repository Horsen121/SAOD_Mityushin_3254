#!/bin/sh
valgrind ./task4 —tool=memcheck
valgrind ./task4 —leak-check=full