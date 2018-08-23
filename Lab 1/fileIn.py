
#from subprocess import call
import os
import time

from datetime import datetime as dt

try:
    import Queue as Q  # ver. < 3.0
except ImportError:
    import queue as Q

class process_obj(object):
	at=0
	bt=0
	
	
	"""docstring for proccess_obj"""
	def __init__(self,secs,size,fname,pid):
		super(process_obj, self).__init__()
		self.time=secs
		self.name=fname
		#self.wc=size #if burst time is not equal to size
		if(size==0):# verrrry important
			size=1
		self.bt=size
		self.pid=pid

	def disp(self):
		print "%d  %d  %d  %s "%(self.pid,self.at,self.bt,self.name)
		pass


	def __cmp__(self,other):
		return cmp(self.time,other.time)
		pass


def create_input(q):

	n=0
	plist=[]
	while(q.empty()==False):
		p=q.get()
		p.at=n
		plist.append(p)
		n+=1

	# this is not n
	# plist.sort(key=lambda process_obj:process_obj.wc)

	
	# for y in range(0,n):
	# 	plist[y].bt=y
		
	# 	pass
	#can comment this out afterwards
	plist.sort(key=lambda process_obj:process_obj.pid)
	
	for x in range(0,n):
		plist[x].disp()
		pass


	print "%d is the number "%(n)# tell the number of processes

	f=open("auto_input.txt","w")
	
	f.write("%d"%(n))

	for x in range(0,n):
		f.write("\n%d\n%d"%(plist[x].at,plist[x].bt))
		
		
		pass

	f.close()


def main():
	
	#os.system("ls -g | awk '{print($5,$6,$7,\"#\"$8)}' >out.txt")
	
	#to execute the command in terminal
	os.system(" stat -c \"%Y@%s#%n\" * >out.txt")
	time.sleep(1)
	file =open("out.txt","r")
	x=0

	q=Q.PriorityQueue(maxsize=20)

	#creating the queue
	for line in file:
		if(x==0):
			x+=1
			continue
		ctime=int(line.split("@")[0])
		part2=line.split("@")[1]
		size=int(part2.split("#")[0])
		fname=part2.split("#")[1] 
		p=process_obj(ctime,size,fname,x-1)
		q.put(p)
		x+=1
		print(ctime)
		print(size)
		print(fname)

	
	create_input(q)
	file.close()
	pass






if __name__ == '__main__':
	main()