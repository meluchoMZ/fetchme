# FetchMe
A simple system info fetching tool

## Installation
To be able to use this tool you must have in your system gcc and make (the program outputs information in coloured text, so the terminal emulation must be compatible).
1. Clone this repository
2. Execute on a terminal: make
3. (Optional) Add the executable to the path

## Media
Execution example:
```
                     .
                    / V\
                  / `  /
                 <<   |
                 /    |
               /      | 	 OS: Debian GNU/Linux 10 (buster)
             /        | 	 Kernel: Linux version 4.19.0-14-amd64
           /    \  \ /  	 Up: 50 min
          (      ) | |  	 CPU:  Intel(R) Core(TM) i7-4510U CPU @ 2.00GHz
  ________|   _/_  | |  	 Memory: 2856 MB / 16316 MB
/__________\______)\__)


```

## Troubleshooting
If something goes wrong, the program will output the missing information with the sentence
> unaccesible info! :-(


If this happens to you make sure you have the files /etc/os-release /proc/version /proc/cpuinfo /proc/meminfo and /proc/uptime
If you are experience any other problem, please fell free to contact so I can fix it as soon as posible

However, this is only a very early version and is intented as personal use only

## TO DO
1. Multiple ascii art
2. More information
3. Log file for debugging
