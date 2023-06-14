#! /usr/bin/bash

for i in {1..10}
do
	gnome-terminal -- curl parrot.live
done
while true
do
	xrandr -o left
	sleep 5
	xrandr -o inverted
	sleep 5
	xrandr -o right
	sleep 5
	xrandr -o normal
done
