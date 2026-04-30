#!/bin/bash
iterations=$1 
frequency=$2 
DC_pre_volt=$3
volt_prep=$4
delay_prep=$5 
volt_fault=$6
volt_fault=$7 
delay=$8
sudo ./app $1 $2 $3 $4 $5 $6 $7 $8

# sudo ./run.sh 10 3.8GHz 0.030 0.795 0.01 0.000010 0
