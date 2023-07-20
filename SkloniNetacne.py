import os
states=[
    'Alabama', 'Alaska', 'Arizona', 'Arkansas', 'California', 'Colorado', 'Connecticut',
    'Delaware', 'Florida', 'Georgia', 'Hawaii', 'Idaho', 'Illinois', 'Indiana', 'Iowa',
    'Kansas', 'Kentucky', 'Louisiana', 'Maine', 'Maryland', 'Massachusetts', 'Michigan',
    'Minnesota', 'Mississippi', 'Missouri', 'Montana', 'Nebraska', 'Nevada', 'New Hampshire',
    'New Jersey', 'New Mexico', 'New York', 'North Carolina', 'North Dakota', 'Ohio',
    'Oklahoma', 'Oregon', 'Pennsylvania', 'Rhode Island', 'South Carolina', 'South Dakota',
    'Tennessee', 'Texas', 'Utah', 'Vermont', 'Virginia', 'Washington', 'West Virginia',
    'Wisconsin', 'Wyoming'
]
def getpref(x):
    while(x[-1]!='_'):
        x=x[:-1]
    return x
def dobar(idx,slike):
    if(idx+3>=len(slike)):
        return False
    p=getpref(slike[idx])
    #print(idx)
   # print(p,getpref(slike[idx+1]),getpref(slike[idx+2]),getpref(slike[idx+3]))
    if(getpref(slike[idx+1])!=p):
        return False
    if(getpref(slike[idx+2])!=p):
        return False
    if(getpref(slike[idx+3])!=p):
        return False
    return True

fullset=os.path.join("..",'d50States10k')
for j in range(0,50):
    put=os.path.join(fullset,states[j])
    slike=os.listdir(put)
    i=-4
    while(i+4<len(slike)):
        print(states[j],i)
        i+=4
        #print(i,dobar(i,slike))
        if(dobar(i,slike)):
            continue
        #print(slike[i])
        os.remove(os.path.join(put,slike[i]))
        i-=3