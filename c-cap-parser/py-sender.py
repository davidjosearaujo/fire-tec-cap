#
#   Runs with:  python3 py-sender.py
#
import socket
import capparser

#alert = capparser.parse(filePath="../FireTec_Example.xml")

HOST = '192.168.0.100'  # The remote host
PORT = 50005         #The same port as used by the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'Hello World')
    data = s.recv(1024)
    #s.sendall(bytes(capparser.deparse(alert)))
print('Received', repr(data))
