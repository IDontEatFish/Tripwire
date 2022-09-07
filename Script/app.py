import serial.tools.list_ports
from send_sms import send_sms
import time

ports = serial.tools.list_ports.comports()

serialInst =  serial.Serial()

portList = []

serialInst.baudrate = 9600
serialInst.port = 'COM4'
serialInst.open()
pTime = time.time()


while True:
    if serialInst.in_waiting: # if data in buffer
        packet = serialInst.readline() # read incoming bytes
        byte = packet.decode('utf')

        data = byte[:-2]
        print(data)

        try:
            if time.time() - pTime > 10:
                if float(byte) < 6.00:
                    send_sms()
                    pTime = time.time()
        except:
            print(byte, data)
            

         
