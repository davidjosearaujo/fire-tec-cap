#
#   Runs with:  python py-sender.py
#
import socket
import capparser

alert = capparser.parse(filePath="../FireTec_Example.xml")

HOST = 'localhost'  # The remote host
PORT = 9090         #The same port as used by the server
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    # Alert object must be converted into a string and then to bytes
    s.sendall(bytes(capparser.deparse(alert)))
