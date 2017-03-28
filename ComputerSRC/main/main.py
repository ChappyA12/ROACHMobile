#helper libraries
from multiprocessing import Process
#process files
import DIRFile as DF
import MAGNFile as MF

DIR = Process(target=DF.DIRProcess, args=())
MAGN = Process(target=MF.MAGNProcess, args=())

def main():
	DIR.start()
	MAGN.start()

if __name__ == "__main__":
	main()