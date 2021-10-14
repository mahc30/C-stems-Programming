from ecdsa import SigningKey, NIST224p
import time
import psutil
import threading
from threading import Timer

# Se generan las llaves
sk = SigningKey.generate() # uses NIST192p
#sk = SigningKey.generate(curve = NIST224p) 
vk = sk.verifying_key

def sign():
    while(True):
        time.sleep(0.2) # Prevenir 100% de uso de cpu por ciclo infinito
        sk.sign(b"Mahc000148441") #Firma

signature = sk.sign(b"Mahc000148441") #Firma
def verify():
    while(True):
        time.sleep(0.2) # Prevenir 100% de uso de cpu por ciclo infinito
        vk.verify(signature, b"Mahc000148441")

class DisplayCPU(threading.Thread):

    cpuUsageMeasures = []
    running = False
    
    def run(self):
        t = Timer(10.0, self.stop)
        self.running = True
        t.start()

        currentProcess = psutil.Process() 
        
        print("CPU usage (%) while running function (Ctrl + C to end): ")
        while self.running:
            # Por tanteo el intervalo que permite 
            # ver la mayor cantidad de medidas es 0.2
            usage = currentProcess.cpu_percent(interval=0.03)
            self.cpuUsageMeasures.append(usage)
            #print(usage)
        
        self.report()
        
    def stop(self):
        self.running = False

    def cpuUsageAvg(self):
        filteredMeasures = list(filter(lambda a: a != 0, self.cpuUsageMeasures))
        promedio = sum(filteredMeasures) / len(filteredMeasures)
        return promedio

    def maxCpuUsage(self):
        return max(self.cpuUsageMeasures)

    def report(self):
        print("Promedio de uso de CPU (%) durante ejecución: " + str(round(self.cpuUsageAvg(),2)) + "%")
        print("Max CPU usage: " + str(round(self.maxCpuUsage(),2)) + "%")
        print("CTRL + C to exit")

display_cpu = DisplayCPU()
display_cpu.start()

try:
    # Función a probar (Solo funciona la que aparezca primero)
    result = verify()
    result = sign()
except KeyboardInterrupt: # stop thread when Ctrl+C
    display_cpu.stop()

# Adaptado de: https://stackoverflow.com/questions/58403391/how-to-monitor-usage-of-cpu-when-function-is-called-in-python-psutil