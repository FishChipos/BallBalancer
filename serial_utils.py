import serial
from serial.tools import list_ports

def get_arduino_port():
    '''
    Expects the board to reply with "OK".
    '''
    ports = [port.name for port in list_ports.comports()]
    print(ports)
    
get_arduino_port()
    