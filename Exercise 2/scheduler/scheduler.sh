#!/bin/bash
if [ $# -lt 2 ] || [ $# -gt 3 ]; then
  echo "Usage: scheduler <policy> [<quantum>] <input_filename>"
  echo "Policies: FCFS, SJF, RR, PRIO"
  exit 1
fi

policy=$1
input_file=$3
quantum=""
if [ "$policy" = "RR" ] || [ "$policy" = "PRIO" ]; then
  if [ $# -ne 3 ]; then
    echo "Usage: scheduler <policy> [<quantum>] <input_filename>"
    echo "Policies: FCFS, SJF, RR, PRIO"
    exit 1
  fi
  quantum="-q $2"
fi

./scheduler "$policy" $quantum < "$input_file"
