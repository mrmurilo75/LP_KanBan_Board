#!/bin/bash

gcc -Wall -o bin/main src/main.c 
if ls | grep text.txt
then
	rm text.txt
fi 
if ls | grep author.txt
then
	rm author.txt
fi 
if ls | grep cards.bin
then
	rm cards.bin
fi 
./bin/main < fill.in && ./bin/main < test.in

