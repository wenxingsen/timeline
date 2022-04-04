# timeline
A tool likes time command, which outputs more real-time log.

latest version: 0.2 beta.

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

2022.04.04 0.2 beta: support specified time format and improve time accuracy

2022.04.01 0.1 beta: init commit

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
A tool likes 'time' command, which outputs time in every line log.
version: 0.2 beta.

Usage:
	timeline [cmd]
Exeample:
	timeline make
	timeline ./demo-cmd.sh
	timeline ping baidu.com
Config:
	 env: TIMELINE_FORMAT, defualt is '%Y-%m-%d %H:%M:%S'
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
[2022-04-04 13:12:24 0m0.002s] You
[2022-04-04 13:12:24 0m1.003s] are
[2022-04-04 13:12:25 0m2.004s] the
[2022-04-04 13:12:26 0m3.006s] one
[2022-04-04 13:12:27 0m4.007s] !!!
[2022-04-04 13:12:28 0m5.008s] <<< the end

cost time: 0m5.008s, return code: 0
```

timeline is very helpful, especially when using 'make' during compilation.

# advanced config

You can specify the time display format

only show cost time:

```
export TIMELINE_FORMAT=""
```

result:

```
$ timeline ./demo-cmd.sh
[0m0.003s] You
[0m1.004s] are
[0m2.017s] the
[0m3.019s] one
[0m4.020s] !!!
[0m5.021s] <<< the end

cost time: 0m5.021s, return code: 0
```

only show clock and cost time:

```
export TIMELINE_FORMAT="%H:%M:%S"
```
result:

```
$ timeline ./demo-cmd.sh
[13:16:27 0m0.002s] You
[13:16:27 0m1.003s] are
[13:16:28 0m2.004s] the
[13:16:29 0m3.006s] one
[13:16:30 0m4.007s] !!!
[13:16:31 0m5.008s] <<< the end

cost time: 0m5.008s, return code: 0
```
