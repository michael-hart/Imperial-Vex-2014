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

        # Check length of command list to see if data is waiting
        self.command_list = []
        self.command_lock = threading.Lock()
    
    def write(self, s):
        """ Writes the string s to the serial port """
        assert type(s) == str
        self.serial.write(s)
        
    def poll(self):
    	if continue_thread == False:
    		cleanup()
    		return
        waiting = self.serial.inWaiting()
        if waiting > 0:
            self.buffer += self.serial.read(waiting)
            # Check fletcher of first five bytes
            if len(self.buffer) > 4:
                if fletcher.compare_checksum(self.buffer[:3], self.buffer[3:5]):
                    # Fletcher checks out, append to command list and delete from buffer
                    self.add_command_thread_safe(self.buffer[:5])
                    self.buffer = self.buffer[5:]
                    print "Command added normally. Command,Data is:"
                else:
                    # Fletcher not checked out. Either packet is corrupt or we're out of sync
                    # Iterate over list until a valid checksum appears and destroy previous data.
                    for i in range(len(self.buffer)):
                        if fletcher.compare_checksum(self.buffer[i:i+3], self.buffer[i+3:i+5]):
                            self.add_command_thread_safe(self.buffer[i:i+5])
                            self.buffer = self.buffer[i+5:]
                            print "Forced to resync. Command,Data is:"
                            break
        else:
            time.sleep(10)

    def add_command_thread_safe(self, cmd):
        while self.command_lock.locked():
            # Wait for lock to clear
            time.sleep(0.001)
        with self.command_lock:
            self.command_list += (cmd[0], cmd[2])
            print " ".join(map(lambda n: format(ord(n), 'x'), self.command_list[-1]))


    def commands_waiting(self):
        commands = 0
        while self.command_lock.locked():
            # Wait for lock to clear
            time.sleep(0.001)
        with self.command_lock:
            commands = len(self.command_list)
        return commands

    def get_commands_thread_safe(self):
        cmd_copy = []
        while self.command_lock.locked():
            # Wait for lock to clear
            time.sleep(0.001)
        with self.command_lock:
            # list creation copies out the list
            cmd_copy = list(self.command_list)
            self.command_list = []
        return cmd_copy
    
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
