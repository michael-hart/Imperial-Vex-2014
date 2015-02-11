# -*- coding: utf-8 -*-

import serial
import atexit
import threading
import time
import fletcher

ser = None
continue_thread = True

tx_heartbeat = 0x01
tx_forward = 0x02
tx_rotate = 0x04
tx_acknowledge = 0x08
tx_lift_height = 0x10
tx_score = 0x20

rx_heartbeat = 0x01
rx_left_encoder = 0x02
rx_right_encoder = 0x04
rx_acknowledge = 0x08
rx_wake_up = 0x10


class UART:
    """ A class containing methods for RPi UART """
    
    def __init__(self, open_port = "/dev/ttyAMA0", baud_rate=115200):
        """ Opens given port in non-blocking mode at baud rate 115.2k """
        # Set up serial and check that it works correctly
        self.serial = serial.Serial(port=open_port, baudrate=baud_rate, timeout=2)
        self.serial.close()
        self.serial.open()
        assert self.serial.isOpen()
        atexit.register(self.cleanup)
        self.serial.flushInput()
        self.serial.flushOutput()
        # Convert into a thread
        self.thread = threading.Thread(target=self.thread_poll, args=())
        self.thread.daemon = True
        self.thread.start()
        # Set up object variables
        self.buffer = []
        self.command_list = []
        self.command_lock = threading.Lock()
        self.send_buffer = []
        self.send_buffer_lock = threading.Lock()
        self.ack_buffer = []

        self.last_heartbeat_sent = time.time()
        self.current_packet_id = 0
    
    def write(self, s):
        """ Writes the string s to the serial port """
        assert type(s) == str
        self.serial.write(s)

    def thread_poll(self):
    	while continue_thread:
    	    self.poll()
    	    time.sleep(0.01)
    	print "Stopped due to continue_thread is False"
        
    def poll(self):
        # Check for thread killing
    	if continue_thread == False:
    		cleanup()
    		return
        # Read and process any incoming data
        waiting = self.serial.inWaiting()
        if waiting > 0:
            # list does conversion from bytes, which is string, to list of characters
            self.buffer += map(ord, list(self.serial.read(waiting)))
            self.process_rcv_buffer()

        # Check for last hearbeat, and send new one if necessary
        if time.time() - self.last_heartbeat_sent > 0.03:
            self.last_heartbeat_sent = time.time()
            self.heartbeat()

        # Write any waiting commands and acknowledges
        # First, wait for lock
        while self.send_buffer_lock.locked():
            time.sleep(.001)
        with self.send_buffer_lock:
            # Iterate over list and send each command
            for cmd in self.send_buffer:
                # Do we need an acknowledge?
                if (cmd[0] == 0x2 or cmd[0] == 0x4 or cmd[0] ==  0x10):
                    ack_buffer.append( (cmd, time.time()) )
                # Send!
                self.serial.write(''.join(map(chr,cmd)))


    def process_rcv_buffer(self):
        """ Uses self.buffer ONLY. """
        # Check fletcher of first five bytes
        if len(self.buffer) > 4:
            if fletcher.compare_checksum(self.buffer[:3], self.buffer[3:5]):
                # Fletcher checks out, append to command list and delete from buffer
                if (self.buffer[0] == rx_wake_up or self.buffer[0] == rx_left_encoder or self.buffer[0] == rx_right_encoder):
                    self.acknowledge(buffer[1])
                self.add_command_thread_safe(self.buffer[:5])
                self.buffer = self.buffer[5:]
            else:
                # Fletcher not checked out. Either packet is corrupt or we're out of sync
                # Iterate over list until a valid checksum appears and destroy previous data.
                for i in range(len(self.buffer)-4):
                    if fletcher.compare_checksum(self.buffer[i:i+3], self.buffer[i+3:i+5]):
                        if (self.buffer[i] == rx_wake_up or self.buffer[i] == rx_left_encoder or self.buffer[i] == rx_right_encoder):
                            self.acknowledge(buffer[i+1])
                        self.add_command_thread_safe(self.buffer[i:i+5])
                        self.buffer = self.buffer[i+5:]
                        break

    def add_command_thread_safe(self, cmd):
        while self.command_lock.locked():
            # Wait for lock to clear
            time.sleep(0.001)
        with self.command_lock:
            self.command_list.append(tuple([cmd[0], cmd[2]]))
	    print " ".join([hex(ord(x)) for x in self.command_list[-1]])

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

    # Define all commands that can be sent
    def build_command(self, cmd, data):
        # Build packet
        packet = [cmd, self.current_packet_id, data]
        self.current_packet_id = (self.current_packet_id + 1) % 255
        checksum = fletcher.fletcher16(packet)
        packet += [(checksum >> 8) & 0xFF, checksum & 0xFF]
        # Thread-safe add to buffer
        while self.send_buffer_lock.locked():
            time.sleep(0.001)
        with self.send_buffer_lock:
            self.send_buffer.append(packet)

    def heartbeat(self):
        self.build_command(tx_heartbeat, 0x00)

    def forward(self, data):
        self.build_command(tx_forward, data)

    def rotate(self, data):
        self.build_command(tx_rotate, data)

    def acknowledge(self, data):
        self.build_command(tx_acknowledge, data)

    def score(self):
        self.build_command(tx_score, 0x00)

    def lift_height(self, data):
        self.build_command(tx_lift_height, data)
    
    def cleanup(self):
        continue_thread = False
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
    	try:
            uart.write("".join(map(chr,[1, 0x22, 0, 0x47, 0x23])))
            time.sleep(5)
    	except KeyboardInterrupt:
    	    continue_thread = False
    	    return

if __name__ == '__main__':
    uart_main()
