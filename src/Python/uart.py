# -*- coding: utf-8 -*-

import Adafruit_BBIO.UART as UART
import serial
import atexit
import threading
import time

ser = None

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
        c = self.serial.read()
        if len(c) > 0:
            self.buffer += self.serial.read()
            # Split buffer into five and check fletcher
            return self.buffer[-1]
        else:
            time.sleep(10)
    
    def cleanup(self):
        self.serial.close()
        self.thread.stop()
        # Not yet implemented, but will be done
        # UART.cleanup()
        
def uart_main():
    uart = BB_UART()
    if uart == None:
        print "Failed to open"
        return
    uart.write("Hello, World!")
    print "Port open. Listening..."
    while True:
        s = uart.poll()
        if len(s) > 0:
            print s

if __name__ == '__main__':
    uart_main()
