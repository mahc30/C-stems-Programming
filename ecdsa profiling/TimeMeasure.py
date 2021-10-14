# Miguel Ángel Hincapié Calle
# ID: 000148441
# ECC utilizadas: NIST192p, NIST 224p

import time
from ecdsa import SigningKey, NIST224p
import numpy as np
import matplotlib.pyplot as plt

nist192SignTime = []
nist192VerifyTime = []

# Se generan las llaves
sk = SigningKey.generate() # uses NIST192p
vk = sk.verifying_key

print("Obteniendo promedio de tiempo para NIST192p")
for i in range(0,100):
    #print("Tiempo para firmar usando NIST192p")
    # Se toma el tiempo antes de firmar
    start_time = time.time()
    signature = sk.sign(b"Mahc000148441") #Firma
    total_time = time.time() - start_time # Se calcula la diferencia de tiempo

    nist192SignTime.append(total_time)
    #print("--- %s seconds ---" %  total_time)

    #print("Tiempo para verificar usando NIST192p")
    # Se toma el tiempo antes de Verificar
    start_time = time.time()
    vk.verify(signature, b"Mahc000148441")
    total_time = time.time() - start_time # Se calcula la diferencia de tiempo

    nist192VerifyTime.append(total_time)

    #print("--- %s seconds ---" %  total_time)

nist224SignTime = []
nist224VerifyTime = []

# Se generan las llaves nuevamente pero ahora usando NIST224p
sk = SigningKey.generate(curve=NIST224p)
vk = sk.verifying_key

print("Obteniendo promedio de tiempo para NIST224p")
for i in range(0,100):
    # Se toma el tiempo antes de firmar
    start_time = time.time()
    signature = sk.sign(b"Mahc000148441") #Firma
    total_time = time.time() - start_time # Se calcula la diferencia de tiempo

    nist224SignTime.append(total_time)
    #print("--- %s seconds ---" %  total_time)

    # Se toma el tiempo antes de Verificar
    start_time = time.time()
    vk.verify(signature, b"Mahc000148441")
    total_time = time.time() - start_time # Se calcula la diferencia de tiempo
    nist224VerifyTime.append(total_time)

    #print("--- %s seconds ---" %  total_time)

def promedio(arr):
    acumulado = 0
    for i in range(0, len(arr)):
        acumulado = acumulado + arr[i]

    return acumulado / len(arr)

promedioFirmaNist192 = promedio(nist192SignTime)
promedioVerificacionNist192 = promedio(nist192VerifyTime)
promedioFirmaNist224 = promedio(nist224SignTime)
promedioVerificacionNist224 = promedio(nist224VerifyTime)

print("Tiempo promedio de Firma con Nist192: " + str(promedioFirmaNist192))
print("Tiempo promedio de Verificación con Nist192: " + str(promedioVerificacionNist192))
print("Tiempo promedio de Firma con Nist224: " + str(promedioFirmaNist224))
print("Tiempo promedio de Verificación con Nist224: " + str(promedioVerificacionNist224))

# plotting
# x = np.arange(0, 100)

'''
plt.title("Comparación de tiempos de firmado NIST192 vs NIST224")
plt.xlabel("Intento")
plt.ylabel("Tiempo (s)")
plt.plot(x, nist192SignTime, color ="red")
plt.plot(x, nist224SignTime, color ="blue")
plt.show()
'''

'''
plt.title("Comparación de tiempos de Verificación NIST192 vs NIST224")
plt.xlabel("Intento")
plt.ylabel("Tiempo (s)")
plt.plot(x, nist192VerifyTime, color ="red")
plt.plot(x, nist224VerifyTime, color ="blue")
plt.show()
'''