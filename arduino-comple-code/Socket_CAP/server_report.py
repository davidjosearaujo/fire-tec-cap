import socket
import time
from gtts import gTTS
from pydub import AudioSegment
import random

def server_program():
  
  host= '192.168.0.23'
  port = 8080
    
  print("[+]Creating new socket...")
  server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  server_socket.bind((host, port))  # bind host address and port together
  print(" [+]Listening...")
  server_socket.listen(2)
  conn, address = server_socket.accept()  # accept new connection
  data=b'?'
  conn.sendall(data)
  print(" [+]Waiting data from client...")
  receives = conn.recv(1024)#.decode()
  if not receives:
    print(" NOT RECEIVE DATA")
  print(' Received from client: ' + receives.decode())  # show in terminal
    
  print("[-]Closing new Socket")
  conn.close()  # close the connection

if __name__ == '__main__':
    server_program()