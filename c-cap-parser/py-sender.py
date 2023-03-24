#
#   Runs with:  python3 py-sender.py 192.168.1.100:50005
#
import base64
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

    # FEATURE - Converting mp3 to wav
    byts = mp3_to_wav(myobj)

    # Defining new field for the next CAP xml
    resource.setDerefUri(str(base64.b64encode(byts)))
    info.getResources()[0] = resource
    alert.getInfos()[0] = info
    capparser.writeAlertToFile(alert, "test.xml")
    
    # TESTING
    exit()

    addr = sys.argv[1].split(':')
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((addr[0], (int)(addr[1])))
        xml = capparser.deparse(alert)
        s.sendall(bytes(xml))


# Convert mp3 object to wav byte array text
def mp3_to_wav(mp3_obj):
    mp3_obj.save("temp.mp3")
    
    # TESTING - WAV conversion
    #sound = AudioSegment.from_mp3("temp.mp3")
    #sound = sound.set_frame_rate(16000)
    #sound = sound.set_sample_width(1)
    #sound.export("temp.wav", format="wav")
    
    byts = None
    # TESTING
    #with open("temp.wav", "rb") as f:
    with open("temp.mp3", "rb") as f:
        byts = f.read()
        f.close()
    
    return byts

if __name__ == "__main__":
    run()