import random
import numpy as np 	

def generate(N, filePath):
	a = random.sample(range(1, N+1), N)
	b = sorted(np.random.random((1,N))[0], reverse=True)
	dataSet=zip(a, b)

	"""
	resultData=""
	for pairs in dataSet:
	    resultData=resultData+(str(pairs[0])+" "+str(pairs[1]))+"\n"
	
	with open(filePath, 'a') as the_file:
	     the_file.write(resultData)
	"""
	count=0
	with open(filePath, 'a') as the_file:
		for pairs in dataSet:
		    count=count+1
		    the_file.write((str(pairs[0])+" "+str(pairs[1]))+"\n")
		    if (count%10000==0):
			print(count)

#generate(1000000, "/home/dbis/workspace/ParallelTopK/postingList4-1000000.txt")
#generate(1000000, "/home/dbis/workspace/ParallelTopK/postingList5-1000000.txt")
#generate(1000000, "/home/dbis/workspace/ParallelTopK/postingList6-1000000.txt")
#generate(1000000, "/home/dbis/workspace/ParallelTopK/postingList7-1000000.txt")
#generate(1000000, "/home/dbis/workspace/ParallelTopK/postingList8-1000000.txt")
#generate(1000000, "/home/dbis/workspace/ParallelTopK/postingList3-1000000.txt")
#generate(1000000, "/home/dbis/workspace/ParallelTopK/postingList9-1000000.txt")
#generate(1000000, "/home/dbis/workspace/ParallelTopK/postingList10-1000000.txt")
generate(1000000, "/home/dbis/workspace/ParallelTopK/postingList12-1000000.txt")

