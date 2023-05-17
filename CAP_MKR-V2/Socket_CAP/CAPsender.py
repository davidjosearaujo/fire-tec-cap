#
#   Runs with:  python3 CAPsender.py 192.168.0.23:8080 hex|base64
#
import base64
import binascii
import socket
import capparser
import sys, os
from gtts import gTTS
from pydub import AudioSegment
#from pydub import AudioSegment

def run():
    alert = capparser.parse(filePath="FireTec_Example.xml")
    info = alert.getInfos()[0]

    resource = capparser.Resource()
    resource.setResourceDesc("Audio Message")
    resource.setMimeType("audio/wav")

    # Generating audio
    myobj = gTTS(
        text=""" Atenção, incêndio na autoestrada 1, perto de Alvelos, Barcelos. Por favor, circule com cuidado. """,
        lang='pt-PT',
        slow=False)

    byts = mp3_to_wav(myobj)
    
    # Convert bytes to string representation of hex values
    if sys.argv[2] == 'hex':
        resource.setDerefUri(binascii.hexlify(byts).decode('utf8'))
    elif sys.argv[2] == 'base64': # Or to base64 encoded string
        resource.setDerefUri(str(base64.b64encode(byts))[2:-1])
    else:
        print("No format specified")
        exit()
    
    # Adding resource to alert and write new file
    info.getResources()[0] = resource
    alert.getInfos()[0] = info
    capparser.writeAlertToFile(alert, "test.xml")
    
    addr = sys.argv[1].split(':')
    
    host= addr[0]
    port = int(addr[1])
    #host = socket.gethostname()
    #port = 5000  # initiate port no above 1024

    print("[+]Creating socket....")
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
      # get instance
    # look closely. The bind() function takes tuple as argument
    server_socket.bind((host, port))  # bind host address and port together

    # configure how many client the server can listen simultaneously
    print("[+]Listening....")
    server_socket.listen(2)
    conn, address = server_socket.accept()  # accept new connection
    print("[+]Socket accept ....")
    print("Connection from: " + str(address))
    
    #------send------------
    print("[+]Sending data ....")
    xml = capparser.deparse(alert)
    conn.sendall(bytes(xml))
    
    


# TODO
# Convert mp3 object to wav byte array text
def mp3_to_wav(mp3_obj):
    mp3_obj.save("temp.mp3")    
    byts = None
    
    sound = AudioSegment.from_mp3("temp.mp3")
    sound = sound.set_frame_rate(44100)
    sound = sound.set_sample_width(1)
    sound.export("2Send.wav", format="wav")
    File="2Send.wav"
    
    with open(File, "rb") as f:
        byts = f.read()
        f.close()
    return byts

if __name__ == "__main__":
    run()