import os
from re import L
import numpy as np
import shutil

main_folder = ".."
fullset=os.path.join(main_folder,'d50States10k')
trainset=os.path.join(main_folder,'TrainSet')
testset=os.path.join(main_folder,'TestSet')

def radistate(state):
    path= os.path.join(fullset,state) 
    dtren=os.path.join(trainset,state)
    dtest=os.path.join(testset,state)
    if not os.path.exists(dtren):
        os.makedirs(dtren)
    if not os.path.exists(dtest):
        os.makedirs(dtest)
    fajlovi = os.listdir(path)
    for i in range(0,len(fajlovi)):
        if i//4<2250:
            dest=dtren
        else:
            dest=dtest
        shutil.copy(os.path.join(path,fajlovi[i]),os.path.join(dest,fajlovi[i]))


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

for i in range(0,50):
    radistate(states[i])