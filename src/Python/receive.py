import fletcher
import time
class receive_master:
    last_rec_iD = -1
    received_instr_set = []
    time_last = time.time()
    
    def heartbeat(x):
        print 1
        return 1
    def rec_left_data(x,data):
        print data
        return data
    def rec_right_data(x,data):
        print data
        return data
    def acknowledge(x,data):
        print data
        return data
    def wakeup(x):
        print 5
        return 5
    def nop(x):
        print 0
        return 0
    def invalid_cmd(x):
        print -1
        return -1
    def rcv_msg(self, cmd):
        if cmd == '\x00\x00\x00\x06\x07':
            print 'nop'
        elif (ord(cmd[1]) > self.last_rec_iD):
            self.last_rec_iD = ord(cmd[1])
            if fletcher.compare_checksum(cmd[0:3],cmd[3:5]):
                self.time_last = time.time()
                self.received_instr_set.append([ord(cmd[0]),ord(cmd[2])])
                return self.act_cmd(ord(cmd[0]),ord(cmd[2]))
            else:
                print 'failchk'
        else:
            print 'failiD'

    def act_cmd(self, chr, data):
        if chr == 1:
            return self.heartbeat()
        elif chr == 2:
            return self.rec_left_data(data)
        elif chr == 3:
            return self.rec_right_data(data)
        elif chr == 4:
            return self.acknowledge(data)	
        elif chr == 5:
            return self.wakeup()
        elif chr ==0:
            return self.nop()
        else:
		    return self.invalid_cmd()
				