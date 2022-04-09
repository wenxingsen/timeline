# timeline
A tool likes 'time' command, which outputs time in every line log.

latest version: 0.3 beta.

quick preview:
```
$ timeline ping wenxingsen.com -c 4
[2022-04-04 13:06:31 0m0.376s] PING wenxingsen.com (182.254.247.93) 56(84) bytes of data.
[2022-04-04 13:06:31 0m0.377s] 64 bytes from 182.254.247.93 (182.254.247.93): icmp_seq=1 ttl=50 time=33.6 ms
[2022-04-04 13:06:31 0m1.222s] 64 bytes from 182.254.247.93 (182.254.247.93): icmp_seq=2 ttl=50 time=33.5 ms
[2022-04-04 13:06:32 0m2.223s] 64 bytes from 182.254.247.93 (182.254.247.93): icmp_seq=3 ttl=50 time=33.5 ms
[2022-04-04 13:06:33 0m3.225s] 64 bytes from 182.254.247.93 (182.254.247.93): icmp_seq=4 ttl=50 time=33.5 ms
[2022-04-04 13:06:34 0m3.225s] 
[2022-04-04 13:06:34 0m3.225s] --- wenxingsen.com ping statistics ---
[2022-04-04 13:06:34 0m3.225s] 4 packets transmitted, 4 received, 0% packet loss, time 3004ms
[2022-04-04 13:06:34 0m3.225s] rtt min/avg/max/mdev = 33.529/33.556/33.608/0.226 ms
[2022-04-04 13:06:34 0m3.225s] <<< the end
cost time: 0m3.225s, return code: 0
```

# changlog
2022.04.09 0.3 beta: support print every sec when no output log

2022.04.04 0.2 beta: support specified time format and improve time accuracy

2022.04.01 0.1 beta: init commit

# build
```
sh build.sh
```
You will get:
```
+ gcc timeline.c -o timeline -std=gnu99 -lpthread -Wall -Werror
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
A tool likes 'time' command, which outputs time in every line log.
version: 0.3 beta.

Usage:
	timeline [cmd]
Exeample:
	timeline make
	timeline ./demo-cmd.sh
	timeline ping baidu.com
Config:
	 env: TIMELINE_FORMAT, defualt is '%Y-%m-%d %H:%M:%S'
	 env: PRINT_EVERY_SEC, defualt is none
```

# why timeline is good?

The 'time' cmd only can get the 'time consuming' after the program ends.

The 'timeline' tool can get the time in real time instead of waiting until the program ends. 

such as follow bash:

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
sleep 5
```

use 'time' cmd:

```
$ time ./demo-cmd.sh 
You
are
the
one
!!!

real	0m9.009s
user	0m0.003s
sys	0m0.004s
```

use 'timeline' cmd:

```
$ timeline ./demo-cmd.sh 
[2022-04-09 21:49:07 0m00.002s] You
[2022-04-09 21:49:08 0m01.003s] are
[2022-04-09 21:49:09 0m02.005s] the
[2022-04-09 21:49:10 0m03.007s] one
[2022-04-09 21:49:11 0m04.008s] !!!
[2022-04-09 21:49:16 0m09.010s] >>> the end

cost time: 0m09.010s, return code: 0
```

timeline is very helpful, especially when using 'make' during compilation.

# advanced config

## TIMELINE_FORMAT

You can specify the time display format

only show cost time:

```
export TIMELINE_FORMAT=""
```

result:

```
$ timeline ./demo-cmd.sh
[0m00.002s] You
[0m01.004s] are
[0m02.005s] the
[0m03.006s] one
[0m04.008s] !!!
[0m09.009s] >>> the end

cost time: 0m09.009s, return code: 0
```

only show clock and cost time:

```
export TIMELINE_FORMAT="%H:%M:%S"
```
result:

```
$ timeline ./demo-cmd.sh
[21:50:21 0m00.003s] You
[21:50:22 0m01.005s] are
[21:50:23 0m02.006s] the
[21:50:24 0m03.008s] one
[21:50:25 0m04.010s] !!!
[21:50:30 0m09.011s] >>> the end

cost time: 0m09.011s, return code: 0
```

## PRINT_EVERY_SEC

when a cmd long time ouput log, you will also not know how long escape, so you can set:

```
export PRINT_EVERY_SEC=1
```
you will get:

```
[2022-04-09 21:51:59 0m00.002s] You
[2022-04-09 21:52:00 0m01.003s] are
[2022-04-09 21:52:01 0m02.005s] the
[2022-04-09 21:52:02 0m03.006s] one
[2022-04-09 21:52:03 0m04.007s] !!!
[2022-04-09 21:52:05 0m06.000s] >>>
[2022-04-09 21:52:06 0m07.000s] >>>
[2022-04-09 21:52:07 0m08.000s] >>>
[2022-04-09 21:52:08 0m09.000s] >>>
[2022-04-09 21:52:08 0m09.009s] >>> the end

cost time: 0m09.009s, return code: 0
```
