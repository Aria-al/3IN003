import matplotlib.pyplot as plt 
import csv 
from os import listdir
from os.path import isfile, join

fileNames = ["TempsAlgo1FonctionK.csv", "TempsAlgo1FonctionS.csv", "TempsAlgo2FonctionK.csv", "TempsAlgo2FonctionS.csv", "TempsAlgo3FonctionS.csv", "TempsAlgo3FonctionK.csv"]


f = fileNames[5]
i = f[9]
c = str(f[-5])
filePath =  f
Names = [] 
Values = [] 

with open(filePath,'r') as csvfile: 
	lines = csv.reader(csvfile, delimiter=',') 
	for row in lines: 
		Names.append(int(row[0])) 
		Values.append(float(row[1])) 

plt.scatter(Names, Values, color = 'g',s = 100) 
plt.xticks(rotation = 25) 
plt.ylabel('Temps(s)') 
plt.xlabel(c) 
if (c[0] != 'K') : 
	X = []			
	k = 20 
	coef = 0 
	for i in range(k) : 
		X.append(Names[int(coef)])
		coef += int (len(Names) / k)
	plt.xticks(X)
plt.title("Algo"+str(i)+"") 
plt.savefig(f[:-4]+".png")

