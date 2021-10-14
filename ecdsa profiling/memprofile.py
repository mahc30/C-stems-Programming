from memory_profiler import memory_usage
from ecdsa import SigningKey, NIST224p

# Se generan las llaves


@profile
def verify192():
    sk = SigningKey.generate() # uses NIST192p
    vk = sk.verifying_key
    signature = sk.sign(b"Mahc000148441") #Firma
    result = vk.verify(signature, b"Mahc000148441")

@profile
def verify224():
    sk = SigningKey.generate(curve=NIST224p) # uses NIST192p
    vk = sk.verifying_key
    signature = sk.sign(b"Mahc000148441") #Firma
    result = vk.verify(signature, b"Mahc000148441")

'''
mem_usage = memory_usage(sign)
print('SIGN PROFILE:')
print('Memory usage (in chunks of .1 seconds): %s' % mem_usage)
print('Maximum memory usage: %s' % max(mem_usage))

mem_usage = memory_usage(verify)
print('VERIFY PROFILE:')
print('Memory usage (in chunks of .1 seconds): %s' % mem_usage)
print('Maximum memory usage: %s' % max(mem_usage))
'''

if __name__ == '__main__':
    #verify192()
    verify224()