#!/usr/bin/expect -f

# connect via scp
#spawn cat /home/user1/Desktop/IPlistfile.txt | while read line do
spawn scp /home/jeetkanjani7/prediction.txt pi@192.168.43.246:Desktop/opencv/opencv-3.1.0/samples/cpp/
#######################
expect {
-re ".*es.*o.*" {
exp_send "yes\r"
exp_continue
}
-re ".*sword.*" {
exp_send "raspberry\r"
}
}
interact

