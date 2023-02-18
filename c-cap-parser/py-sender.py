# Echo client program
import socket
import capparser

alert = capparser.parse(filePath="../FireTec_Example.xml")
print(capparser.deparse(alert))
b = bytes(capparser.deparse(alert))

HOST = 'localhost'  # The remote host
PORT = 9090         #The same port as used by the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b)
