import fletcher
class dispatch_master:
    iD = 0
    def process_cmd(self,cmd):
        return {
	        'hbt':1,
	    	'fwd':2,
			'rot':4,
	    	'ack':8,
	    	'slt':16,
            'scr':32,
	    	}.get(cmd,-1)
    def increment_id(self):
	    self.iD = (self.iD +1) %255
    def generate_msg(self,cmd,data=0):
        self.increment_id()
        l = "".join([chr(self.process_cmd(cmd)), chr(self.iD), chr(data)])
        c = "".join(fletcher.fletcher16_s(l))
        return l+c
				