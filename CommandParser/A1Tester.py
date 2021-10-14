#!/usr/bin/env pythoon
import os , subprocess,sys
P_name=input('Enter project name\n')
if not os.path.exists(P_name):
    print('%s not found in the directory'%P_name)
    sys.exit()
p=0
f=0
out=''
with open ('cases','r') as I: I=I.read().split('\n')
with open ('out','r') as O: O=O.read().split('\n')

for i in range(len(I)-1):
    output=subprocess.getoutput(F'{P_name} {I[i]}')
    try:
        output= output[:-1] if output[-1]==' ' else output
    except:
        output= output
    out=out+'Case '+str(i+1)+'\n'+'input: '.upper()+I[i]+'\nExpected:\n'+O[i]+'\nGenerated:\n'+output
    if output==O[i]:
        p+=1
        out+='\n\n*PASSED*\n'
        out+=20*'-'
        out=out+20*'-'+'\n'
    else:
        f+=1
        out+='\n\n*FAILED*\n'
        out+=20*'-'
        out=out+20*'-'+'\n'
out+=(F'\n\nPassed: {p}\nFailed: {f}')
print(F'\nPassed: {p}\nFailed: {f}\nThe output stored in "output" file')
with open ('output','w') as O: O.write(out)
input('Press any key to exit')
