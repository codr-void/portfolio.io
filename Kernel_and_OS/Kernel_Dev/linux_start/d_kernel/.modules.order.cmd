cmd_/home/codr/ECE373/assignment1/d_kernel/modules.order := {   echo /home/codr/ECE373/assignment1/d_kernel/hello.ko; :; } | awk '!x[$$0]++' - > /home/codr/ECE373/assignment1/d_kernel/modules.order
