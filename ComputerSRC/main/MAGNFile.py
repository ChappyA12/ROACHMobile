import serial

def MAGNProcess():
	#for i in range(100):
	#	print(i)
	ser = serial.Serial("COM7", 9600)
	ser.write(b'2')