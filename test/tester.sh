#! /bin/bash

cd /Users/aagouzou/Desktop/minishell
if [ -f /Users/aagouzou/Desktop/minishell ]; then
    echo "app founded"
else
    make
fi

echo "ls -l" | ./app &
sleep .05;
kill -9 $!

echo "echo "'hello'"" | ./app &
sleep .05;
kill -9 $!

echo "ls -l" | ./app &
sleep .05;
kill -9 $!

echo "ls -l" | ./app &
sleep .05;
kill -9 $!

echo "ls -l" | ./app &
sleep .05;
kill -9 $!
