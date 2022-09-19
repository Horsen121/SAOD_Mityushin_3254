#!/bin/sh
valgrind ./task2 —tool=memcheck
valgrind ./task2 —leak-check=full