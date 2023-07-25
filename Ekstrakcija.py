import os
from re import L
import cv2
import numpy as np
import time
from scipy.ndimage import convolve
from scipy.ndimage import label
from skimage.feature import canny
import skimage
import threading

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

N=256
def prikazi(slika):
    cv2.imshow('Slika',slika)
    cv2.waitKey(0)
def grayscale(slika):
    slikaGray = cv2.cvtColor(slika, cv2.COLOR_BGR2GRAY)
    return slikaGray
def konvolucija(slika,filter):
    return convolve(slika,filter,mode='constant')

def binarizuj(slika, prag):
    a,b=cv2.threshold(slika,prag,255,cv2.THRESH_BINARY)
    return b

def count_comp(slika):
    a,b=label(slika)
    return b
def sve(slika,ouf,c,l1,l2,l3,l4):
    # Boje
    ouf.write(str(np.sum(slika[:, :, 0]))+"\n")
    ouf.write(str(np.sum(slika[:, :, 1]))+"\n")
    ouf.write(str(np.sum(slika[:, :, 2]))+"\n")
    # Linije
    ouf.write(str(count_comp(l1))+"\n")
    ouf.write(str(count_comp(l2))+"\n")
    ouf.write(str(count_comp(l3))+"\n")
    ouf.write(str(count_comp(l4))+"\n")
    # Skupovi boja
    ouf.write(str(np.count_nonzero((slika[:,:,0]>=128) & (slika[:,:,1]>=128) & (slika[:,:,2]>=128)))+"\n")
    ouf.write(str(np.count_nonzero((slika[:,:,0]>=128) & (slika[:,:,1]>=128) & (slika[:,:,2]<128)))+"\n")
    ouf.write(str(np.count_nonzero((slika[:,:,0]>=128) & (slika[:,:,1]<128) & (slika[:,:,2]>=128)))+"\n")
    ouf.write(str(np.count_nonzero((slika[:,:,0]>=128) & (slika[:,:,1]<128) & (slika[:,:,2]<128)))+"\n")
    ouf.write(str(np.count_nonzero((slika[:,:,0]<128) & (slika[:,:,1]>=128) & (slika[:,:,2]>=128)))+"\n")
    ouf.write(str(np.count_nonzero((slika[:,:,0]<128) & (slika[:,:,1]>=128) & (slika[:,:,2]<128)))+"\n")
    ouf.write(str(np.count_nonzero((slika[:,:,0]<128) & (slika[:,:,1]<128) & (slika[:,:,2]>=128)))+"\n")
    ouf.write(str(np.count_nonzero((slika[:,:,0]<128) & (slika[:,:,1]<128) & (slika[:,:,2]<128)))+"\n")
    #Poligoni
    koliko=[0,0,0,0,0,0,0,0]
    poligoni = ~c
    lslika,komp = label(poligoni) 
    for i in range(1,komp+1):
        poz=(lslika[:,:]==i)
        kol=np.sum(lslika[:,:]==i)
        r=np.sum(poz*slika[:,:,0])/kol
        g=np.sum(poz*slika[:,:,1])/kol
        b=np.sum(poz*slika[:,:,2])/kol
        br=0
        br+=4*(r<128)
        br+=2*(g<128)
        br+=1*(b<128)
        koliko[br]+=1
    for i in range(0,8):
        ouf.write(str(koliko[i])+"\n")


def ekstraktuj(slika, ouf):
    gs=grayscale(slika)
    c=canny(skimage.img_as_float(gs), sigma=0.6, low_threshold=0.06, high_threshold=0.5)
    c=c.astype(np.uint8)*255
    l1=konvolucija(c,[[-1,-1,-1],[2,2,2],[-1,-1,-1]])
    l2=konvolucija(c,[[-1,2,-1],[-1,2,-1],[-1,2,-1]])
    l3=konvolucija(c,[[-1,-1,2],[-1,2,-1],[2,-1,-1]])
    l4=konvolucija(c,[[2,-1,-1],[-1,2,-1],[-1,-1,2]])

    sve(slika,ouf,c,l1,l2,l3,l4)
    for i in range(0,4):
        for j in range(0,4):
            sve(slika[i*64:i*64+63,j*64:j*64+63],ouf,c[i*64:i*64+63,j*64:j*64+63],l1[i*64:i*64+63,j*64:j*64+63],l2[i*64:i*64+63,j*64:j*64+63],l3[i*64:i*64+63,j*64:j*64+63],l4[i*64:i*64+63,j*64:j*64+63])


def extr_state(idx):
    state=states[idx%50]
    if idx<50:
        path= os.path.join('..\d50States10k',state) 
        destination = os.path.join("..\Ekstraktovano",state)
    else:
        path= os.path.join('..\d50States2K_test\test_data',state) 
        destination = os.path.join("..\EkstraktovanoTest",state)
    fajlovi = os.listdir(path)

    for i in range(0,len(fajlovi)-1):
        print(state, i, time.time()-start)

        input = os.path.join(path,fajlovi[i])
        slika = cv2.imread(input)
        naziv = str(i//4)+"_"+ str(i%4) +".txt"
        if not os.path.exists(destination):
            os.makedirs(destination)
        output= os.path.join(destination,naziv)
        ouf = open(output,'w')
        ekstraktuj(slika,ouf)

start=time.time()
threads={}

for i in range(0,100):
    threads[i] = threading.Thread(target=extr_state,args=(i,))
for i in range(0,100):
    threads[i].start()
for i in range(0,100):
    threads[i].join()
    #print(slika)