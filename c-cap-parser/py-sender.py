#
#   Runs with:  python3 py-sender.py 192.168.1.100:50005
#
import base64
import binascii
import socket
import capparser
import sys, os
from gtts import gTTS
#from pydub import AudioSegment

def run():
    alert = capparser.parse(filePath="../FireTec_Example.xml")
    info = alert.getInfos()[0]

    resource = capparser.Resource()
    resource.setResourceDesc("Audio Message")
    resource.setMimeType("audio/wav")

    # Generating audio
    myobj = gTTS(
        text='Welcome to geeksforgeeks!',
        lang='en',
        slow=False)

    # Convert bytes to string representation of hex values
    byts = mp3_to_wav(myobj)
    resource.setDerefUri(binascii.hexlify(byts).decode('utf8'))
    
    info.getResources()[0] = resource
    alert.getInfos()[0] = info
    capparser.writeAlertToFile(alert, "test.xml")
    
    addr = sys.argv[1].split(':')
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((addr[0], (int)(addr[1])))
        xml = capparser.deparse(alert)
        s.sendall(bytes(xml))
    s.close()

# TODO
# Convert mp3 object to wav byte array text
def mp3_to_wav(mp3_obj):
    mp3_obj.save("temp.mp3")    
    byts = None
    with open("temp.mp3", "rb") as f:
        byts = f.read()
        f.close()
    return byts

if __name__ == "__main__":
    run()