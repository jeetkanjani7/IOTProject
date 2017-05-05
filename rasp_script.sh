#!/usr/bin/expect

spawn scp /home/pi/Desktop/recognition.png jeetkanjani7@192.168.10.109:
#######################
expect {
-re ".*es.*o.*" {
exp_send "yes\r"
exp_continue
}
-re ".*sword.*" {
exp_send "rishi1234\r"
}
}
interact


