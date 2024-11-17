import matplotlib.pyplot as plt 
import csv 

filePath = "Resultats\\TempsAlgo2FonctionS.csv"
Names = [] 
Values = [] 

with open(filePath,'r') as csvfile: 
	lines = csv.reader(csvfile, delimiter=',') 
	for row in lines: 
		Names.append(int(row[0])) 
		Values.append(float(row[1])) 

plt.scatter(Names, Values, color = 'g',s = 100) 
plt.xticks(rotation = 25) 
plt.ylabel('Temps') 
plt.xlabel('K') 
X = []
for i in Names : 
	if i % 1000 == 0 : 
		X.append(i) 
plt.xticks(Names)
plt.title('Algo 1 en fonction de K', fontsize = 20) 

plt.show() 
