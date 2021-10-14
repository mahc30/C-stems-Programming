import cProfile
from ecdsa import SigningKey, NIST224p

# Se generan las llaves
sk = SigningKey.generate() # uses NIST192p
vk = sk.verifying_key

def sign():
    global signature
    signature = sk.sign(b"Mahc000148441") #Firma

def verify():
    vk.verify(signature, b"Mahc000148441")

print("SIGN NIST192 PROFILE")
cProfile.run("sign()")
print("VERIFY NIST192 PROFILE")
cProfile.run("verify()")

# Se generan nuevas llaves
sk = SigningKey.generate(curve = NIST224p) # uses NIST192p
vk = sk.verifying_key

print("SIGN NIST224 PROFILE")
cProfile.run("sign()")
print("VERIFY NIST224 PROFILE")
cProfile.run("verify()")