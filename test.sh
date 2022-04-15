set -ex

sh build.sh

unset TIMELINE_FORMAT
unset PRINT_EVERY_SEC
unset PRINT_DELTA_TIME
./timeline ping wenxingsen.com -c 4

export TIMELINE_FORMAT=""
unset PRINT_EVERY_SEC
unset PRINT_DELTA_TIME
./timeline ./demo-cmd.sh

export TIMELINE_FORMAT="%H:%M:%S"
unset PRINT_EVERY_SEC
unset PRINT_DELTA_TIME
./timeline ./demo-cmd.sh

unset TIMELINE_FORMAT
export PRINT_EVERY_SEC=1
unset PRINT_DELTA_TIME
./timeline ./demo-cmd.sh

export TIMELINE_FORMAT=""
export PRINT_DELTA_TIME=1
./timeline ./demo-cmd.sh
