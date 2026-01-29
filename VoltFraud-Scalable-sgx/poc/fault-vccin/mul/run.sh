#!/bin/bash
retries=$1
freq=$2
pre_volt=$3
pre_width=$4
fault_volt=$5
fault_width=$6
delay=$7
sudo ./glitch_controller -p -c 1 -d $delay --freq $freq --retries $retries  --pre_volt $pre_volt --pre_width $pre_width --fault_volt $fault_volt --fault_width $fault_width --target_id 0 --iter 100000000 --calc_thread_num 1 --step_count 200 --simple -g

