import dispatch
import receive
import time
import struct

class serial_master:
    pending_ack = {}
    disp = dispatch.dispatch_master()
    rec  = receive.receive_master()
    ack_timeout = 10 #very much a placeholder
    serial_timeout = 10 #very much a placeholder
    
    def dispatch(self):
         cmd = self.disp.dispatch()
         if ((cmd[0] == '\x02') | (cmd[0] == '\x03') | (cmd[0] == '\x05')): #command requires ack
             y = struct.pack('f5p',time.time(), cmd)
             self.pending_ack[cmd[1]] =y
         return cmd
    def push_msg(self,cmd,data=0):
         self.disp.generate_msg(cmd,data)
    def receive(self,cmd):
         result = self.rec.rcv_msg(cmd)
         if cmd[0] == '\x04': #is acknowledge
             try:
                self.pending_ack.pop(chr(result))
             except ValueError:
                print "iD of acknowledge invalid"          
    def check_timeout(self):
         t = time.time()
         if (t - self.rec.time_last) > self.serial_timeout:
             print 'the cortex is dead. everything is lost'
         else:
             for key in self.pending_ack:
                 y = struct.unpack('f5p',self.pending_ack[key])
                 if (y[1] -t) > self.ack_timeout:
                     self.push_msg(y[0][0],y[0][2])
    