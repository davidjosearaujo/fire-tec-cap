#
#   Runs with:  python3 py-sender.py 192.168.1.100:50005
#
import socket
import capparser
import sys
from time import sleep

alert = capparser.parse(filePath="../FireTec_Example_saudio.xml")

addr = sys.argv[1].split(':')

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((addr[0], (int)(addr[1])))
    xml = capparser.deparse(alert)
    s.sendall(bytes(xml))
