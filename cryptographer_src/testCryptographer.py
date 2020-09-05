from subprocess import *

f = open("../tests/randomlyGeneratedStrings.txt", 'r')

lines = f.readlines()

cmdEnc = ["./../cryptographer", "enc", "output/audio.wav", "data_enc_dec/encodings.txt"]
cmdDec = ["./../cryptographer", "dec", "output/audio.wav", "data_enc_dec/decodings.txt"]

noTests = 0
noFailedTests = 0

for line in lines:
    pEnc = Popen(cmdEnc, stdin = PIPE, stdout = PIPE)
    pEnc.stdin.write(line.encode('utf-8'))

    s = (pEnc.communicate()[0]).decode('utf-8').split('\n')
    privKeyP = 0
    privKey = 0
    q = 0

    for data in s:
        if 'privKeyP' in data:
            privKeyP = data.split(' ')[3]
        elif 'privKey' in data:
            privKey = data.split(' ')[3]
        elif 'q        =' in data:
            q = data.split(' ')[10]

    pDec = Popen(cmdDec, stdin = PIPE, stdout = PIPE)
    keys = (str(privKey) + ' ' + str(privKeyP) + ' ' + str(q) + '\n').encode('utf-8')

    pDec.stdin.write(keys)
        
    result = (pDec.communicate()[0]).decode('utf-8').split('\n')
    decoded = ""

    for i in range(0, len(result)): 
        if (result[i] == "Your decoded message is:"):
            decoded = result[i + 1]
            break


    if (decoded != line.strip()):
        print("Original: " + line)
        print("Decoded: " + decoded)
        noFailedTests += 1
    noTests += 1
print ("Passed " + str(noTests - noFailedTests) + " / " + str(noTests) + '\n')
