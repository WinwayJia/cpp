#/bin/bash
perf record -F 99 -p $1 -g -- sleep 30
