import sys
sys.path.append('/home/pi/MasterPi/')
import MjpgServer

def start_streaming():
    server = MjpgServer.Server(port=8080)
    server.start()
    print("Streaming started at http://localhost:8080")

if __name__ == '__main__':
    start_streaming()
