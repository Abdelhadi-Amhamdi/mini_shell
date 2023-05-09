#! /bin/bash

cd ~/Desktop/ds/tree/mini
if [ -f ~/Desktop/ds/tree/mini/app ]; then
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
