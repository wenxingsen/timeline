set -ex
gcc timeline.c -o timeline -std=gnu99 -lpthread -Wall -Werror
echo "build success"
