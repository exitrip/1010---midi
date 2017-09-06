#!/usr/bin/env bash
echo 
echo "WARNING: this program must be used with a suitably recent [after Sept. 2017] firmware build"
echo
if [ $# -eq 3 ] && [ $1 -ne $2 ]
then
    if [ $1 -lt 17 ] && [ $1 -gt 0 ] && [ $2 -lt 17 ] && [ $2 -gt 0 ]
    then
        checksum=$(( ( ( $1 + $2 - 2 ) ^ 0xff ) + 1 ))
        hexCmd=$(printf ":02100000%02X%02X%02X\n" "$(( $1 - 1 ))" "$(( $2 - 1 ))" "$checksum")
        line= `sed -n '/:[0-1]\([0-9A-F]\)100000/ =' $3`
        if [ -z ${line+x} ]
        then
            echo
            echo "target hexfile already has values at address 0x1000"
            echo "overwriting..."
            sed -i "s/:[0-1]\([0-9A-F]\)100000.*/$hexCmd/g" $3
        else
            line=`sed -n '/:[0-1]\([0-9A-F]\)100200/ =' $3`
            echo "inserting $hexCmd into $3 at line $line"
            sed -i "/:[0-1]\([0-9A-F]\)100200/i $hexCmd" $3
        fi
    else
        echo
        echo 'channel out of range'
        echo 'please enter TWO channels between 1 and 16'
        echo
    fi
else
    echo
    echo 'incorrect arguments'
    echo 'please enter TWO DIFFERENT channels between 1 and 16'
    echo 'followed by the target hex file to modify'
    echo 'ex: ./setChannelsInHex.sh 14 16 Blinky.hex'
    echo
fi
#EOF
