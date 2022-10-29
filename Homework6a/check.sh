#!/bin/sh
valgrind ./task —tool=memcheck
valgrind ./task —leak-check=full