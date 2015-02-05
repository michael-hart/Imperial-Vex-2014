# -*- coding: utf-8 -*-

import serial
import atexit
import threading
import time
import fletcher

ser = None
continue_thread = True

class UART:
    """ A class containing methods for RPi UART """
    
    def __init__(self, open_port = "/dev/ttyAMA0", baud_rate=115200):
        """ Opens given port in non-blocking mode at baud rate 115.2k """
        self.serial = serial.Serial(port=open_port, baudrate=baud_rate, timeout=0)
        self.serial.close()
        self.serial.open()
        assert self.serial.isOpen()
        atexit.register(self.cleanup)
	self.serial.flushInput()
	self.serial.flushOutput()
        self.thread = threading.Thread(target=self.poll, args=())
        self.thread.start()
        self.buffer = []
    
    def write(self, s):
        """ Writes the string s to the serial port """
        assert type(s) == str
        self.serial.write(s)
        
    def poll(self):
	if continue_thread == False:
		cleanup()
		return
        c = self.serial.read(5)
        if not c is None:
            self.buffer += c
            # Split buffer into five and check fletcher
            if len(self.buffer) > 4:
            	c = self.buffer[:5]
            	self.buffer = self.buffer[5:]
            	print "fletcher of c is:"
            	print fletcher.fletcher16(c)
            	return " ".join(map(lambda n: format(ord(n), 'x'), c))
        else:
            time.sleep(10)
            return None
    
    def cleanup(self):
        self.serial.close()
        # Not yet implemented, but will be done
        # UART.cleanup()
        
def uart_main():
    uart = UART()
    if uart == None:
        print "Failed to open"
        return
    print "Port open. Listening..."
    while True:
    	result = uart.poll()
    	if not result is None:
    		print result
	time.sleep(0.01)    	

if __name__ == '__main__':
    uart_main()
