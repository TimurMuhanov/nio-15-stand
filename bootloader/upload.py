import serial
import serial.tools.list_ports
import datetime

def int2bytes(int):
	return chr((int & 0xff000000) >> 24) + chr((int & 0x00ff0000) >> 16) + chr((int & 0x0000ff00) >> 8) + chr((int & 0x000000ff) >> 0)

def sendAck():
	return ser.write(chr(_ack)) == 1

def getAck():
	response = ser.read()
	# if(len(response)):
	# 	print "ack", hex(ord(response[0]))
	# else:
	# 	print "ack empty"
	return len(response) and response[0] == chr(_ack)

def sendCmd(cmd):
	ser.write( chr(_begin) + chr(cmd) + chr(0x100-cmd) )
	# print "sending", hex(cmd)
	return getAck()

_begin = 0xFE	
_connect = 0x7F
_go = 0x21
_write = 0x31
_erase = 0x44
_ack = 0x79
_nack = 0x1F
_unknown = 0xFE

addressBase = 0x08040000
pack = 128


# ports = list( serial.tools.list_ports.comports() )
# print "Port list:"
# for p in ports:
#     print p


ser = serial.Serial('COM15')
print "Opened serial port: ", ser.name
ser.timeout = 1.0


# connect
ser.flushInput()
while 1:
	response = ser.read()
	if len(response) and response[0] == chr(_connect):
		sendAck()
		break
ser.flushInput()

print "connected"

firmware = open('firmware.bin', 'rb')
firmwareImage = firmware.read();

if( not sendCmd(_erase) ):
	print "erase command not sended"
	quit()
ser.write( int2bytes(len(firmwareImage)) )

ser.timeout = 100.0
if not getAck():
	print "not erased"
	quit()
ser.timeout = 1.0

print "erased"

index = 0;
while index < len(firmwareImage):
	if( not sendCmd(_write) ):
		print "write command not sended, try again"
		continue
	
	# print "begin ", hex(addressBase+index)
	ser.write( int2bytes(addressBase+index) )
	ser.write( int2bytes(pack) )
	checksum = 0
	for ch in firmwareImage[index:index+pack]:
		checksum = checksum ^ ord(ch)
	ser.write( chr(checksum & 0xff) )
	if not getAck():
		print "header not written, try again"
		continue
	# print "address ", hex(addressBase+index), " ch ", hex(checksum & 0xff)
	ser.write( firmwareImage[index:index+pack] )
	if not getAck():
		print "bytes not written, try again"
		continue
	# print "written", hex(addressBase+index)
	index+=pack

ser.close()             # close port