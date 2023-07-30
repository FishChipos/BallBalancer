import serial
from serial.tools import list_ports

def get_arduino_port():
    '''
    Expects the board to reply with "OK".
    '''
    ports = list_ports.comports()
    print(ports)
    
get_arduino_port()
    