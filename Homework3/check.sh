#!/bin/sh
valgrind ./task3 —tool=memcheck
valgrind ./task3 —leak-check=full