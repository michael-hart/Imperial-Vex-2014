# -*- coding: utf-8 -*-

import Adafruit_BBIO.UART as UART
import serial
import atexit
import threading
import time
import fletcher

ser = None
continue_thread = True

class BB_UART:
    """ A class containing methods for BeagleBoard UART """
    
    def __init__(self, uart_name = "UART1", open_port = "/dev/ttyO1"):
        """ Opens given port in non-blocking mode at baud rate 19.2k,
            or UART1 by default """
        UART.setup(uart_name)
        self.serial = serial.Serial(port=open_port, baudrate=19200, timeout=0)
        self.serial.close()
        self.serial.open()
        assert self.serial.isOpen()
        atexit.register(self.cleanup)
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
            	print "c is:"
            	print c
            	print "fletcher of c is:"
            	print fletcher.fletcher16(c)
            	return hex(' '.join(c))
        else:
            time.sleep(10)
    
    def cleanup(self):
        self.serial.close()
        # Not yet implemented, but will be done
        # UART.cleanup()
        
def uart_main():
    uart = BB_UART()
    if uart == None:
        print "Failed to open"
        return
    print "writing to uart"
    uart.write("dddddddddddddddddd")
    print "Port open. Listening..."
    while True:
	time.sleep(0.01)    	

if __name__ == '__main__':
    uart_main()
