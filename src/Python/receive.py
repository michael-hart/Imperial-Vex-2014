import fletcher
class receive_master:
    last_rec_iD = -1
    def heartbeat(x):
		print 1
    def rec_left_data(x):
	    print 2
    def rec_right_data(x):
		print 3
    def acknowledge(x):
		print 4
    def wakeup(x):
		print 5
    def invalid_cmd(x):
		print -1
    def rcv_msg(self, cmd):
        if (ord(cmd[1]) > self.last_rec_iD):
            self.last_rec_iD = ord(cmd[1])
            if fletcher.compare_checksum(cmd[0:3],cmd[3:5]):
                self.act_cmd(ord(cmd[0]))
        else:
            print 'fail'

    def act_cmd(self, chr):
	    if chr == 1:
		    self.heartbeat()
	    elif chr == 2:
		    self.rec_left_data()
	    elif chr == 3:
		    self.rec_right_data()
	    elif chr == 4:
		    self.acknowledge()	
	    elif chr == 5:
		    self.wakeup()
	    else:
		    self.invalid_cmd()
				