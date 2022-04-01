# timeline
A tool likes time command, which outputs more real-time log.

version: 0.1 beta.

quick preview:
```
$ timeline ping wenxingsen.com -c 4
[2022-04-02 02:14:57][0s] PING wenxingsen.com (182.254.247.93) 56(84) bytes of data.
[2022-04-02 02:14:57][0s] 64 bytes from 182.254.247.93 (182.254.247.93): icmp_seq=1 ttl=50 time=33.6 ms
[2022-04-02 02:14:57][1s] 64 bytes from 182.254.247.93 (182.254.247.93): icmp_seq=2 ttl=50 time=33.5 ms
[2022-04-02 02:14:58][2s] 64 bytes from 182.254.247.93 (182.254.247.93): icmp_seq=3 ttl=50 time=33.5 ms
[2022-04-02 02:14:59][3s] 64 bytes from 182.254.247.93 (182.254.247.93): icmp_seq=4 ttl=50 time=33.6 ms
[2022-04-02 02:15:00][3s] 
[2022-04-02 02:15:00][3s] --- wenxingsen.com ping statistics ---
[2022-04-02 02:15:00][3s] 4 packets transmitted, 4 received, 0% packet loss, time 3011ms
[2022-04-02 02:15:00][3s] rtt min/avg/max/mdev = 33.545/33.587/33.633/0.133 ms
[2022-04-02 02:15:00][3s] <<< the end

cost time: 3s, return code: 0
```

# build
```
sh build.sh
```
You will get:
```
+ gcc timeline.c -o timeline -std=gnu99 -Wall -Werror
+ echo 'build success'
build success
```

# install

```
sudo cp timelime /usr/bin 

# or set PATH to ~/.bashrc
export PATH=/path/to/timeline/dir:$PATH
```

# usage
```
$timeline
A tool likes time command, which outputs more real-time log. version: 0.1 beta.

Usage:
        timeline [cmd]
Exeample:
        timeline make
        timeline ./demo-cmd.sh
        timeline ping baidu.com
```

# why timeline is good?

The 'time' cmd only can get the 'time consuming' after the program ends.

The 'timeline' tool can get the time in real time instead of waiting until the program ends. 

such as follow cmd:

```
#!/bin/bash
echo "You"
sleep 1
echo "are"
sleep 1
echo "the"
sleep 1
echo "one"
sleep 1
echo "!!!"
sleep 
```

use 'time' cmd:

```
$time ./demo-cmd.sh 
You
are
the
one
!!!

real    0m5.013s
user    0m0.005s
sys     0m0.001s
```

use 'timeline' cmd:

```
$timeline ./demo-cmd.sh 
[2022-04-02 01:58:03][0s] You
[2022-04-02 01:58:03][1s] are
[2022-04-02 01:58:04][2s] the
[2022-04-02 01:58:05][3s] one
[2022-04-02 01:58:06][4s] !!!
[2022-04-02 01:58:07][5s] <<< the end

cost time: 5s, return code: 0
```

timeline is very helpful, especially when using 'make' during compilation.