from ecdsa import SigningKey, NIST224p
import psutil
import threading

# Se generan las llaves
#sk = SigningKey.generate() # uses NIST192p
sk = SigningKey.generate(curve = NIST224p) 
vk = sk.verifying_key

def sign():
    while(True):
        signature = sk.sign(b"Mahc000148441") #Firma

def verify():
    signature = sk.sign(b"Mahc000148441") #Firma
    while(True):
        vk.verify(signature, b"Mahc000148441")

class DisplayCPU(threading.Thread):

    def run(self):

        self.running = True

        currentProcess = psutil.Process()

        while self.running:
            print(currentProcess.cpu_percent(interval=1))

    def stop(self):
        self.running = False

display_cpu = DisplayCPU()

print("CPU usage before running function: ")
print(psutil.cpu_percent(interval=5))

print("CPU usage while running function: ")
display_cpu.start()

try:
    result = sign()
    #result = verify()
finally: # stop thread even when I press Ctrl+C
    display_cpu.stop()
