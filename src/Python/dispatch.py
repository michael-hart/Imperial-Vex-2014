import fletcher
class dispatch_master:
    iD = 0
    instr_to_dispatch = []
    def process_cmd(self,cmd):
        return {
		    'nop':0,
	        'hbt':1,
	    	'fwd':2,
			'rot':3,#4,
	    	'ack':4,#8,
	    	'slt':5,#16,
            #'scr':32,
	    	}.get(cmd,-1)
    def dispatch(self):
        if len(self.instr_to_dispatch)==0:
            return '\x00\x00\x00\x06\x07'
        else:
            return self.instr_to_dispatch.pop()
    def increment_id(self):
	    self.iD = (self.iD +1) %255
    def generate_msg(self,cmd,data=0):
        self.increment_id()
        l = "".join([chr(self.process_cmd(cmd)), chr(self.iD), chr(data)])
        c = "".join(fletcher.fletcher16_s(l))
        self.instr_to_dispatch.append(l+c)
        return (l+c)
				