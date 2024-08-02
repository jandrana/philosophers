#!/bin/bash

valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --input-fd=0 --trace-children=yes -s -q ./philo $@