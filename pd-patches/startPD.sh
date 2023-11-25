#!/usr/bin/bash
start=$SECONDS
purr-data -nogui -rt -nosleep -noaudio -open /home/exitrip/1010---midi/pd-patches/oscRouter.pd -open /home/exitrip/1010---midi/pd-patches/midi-tx1-oscIn.pd &
sleep 1
while [[ $(aconnect -l | grep Pure | wc -c) == 0 ]]; do 
	sleep 1
	echo "."
done
#end=$SECONDS
#duration=$(( end - start ))
#echo "dur - $duration"
aconnect 129:1 128:1
aconnect -l
