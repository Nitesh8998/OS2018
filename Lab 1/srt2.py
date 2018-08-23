try:
    import Queue as Q  # ver. < 3.0
except ImportError:
    import queue as Q


# @functools.total_ordering
class process(object):
	at=0
	bt=0
	ct=0
	tat=0
	wat=0
	pid=0
	

	def disp(self):
		print "hi%d %d  %d %d %d %d"%(self.pid,self.at,self.bt,self.ct,self.tat,self.wat)

	def __init__(self):
		self.prio=self.bt

	# def __lt__(self,other):
	# 	return self.prio<getattr(other,'prio',other)


	# def __eq__(self,other):
	# 	return self.prio==getattr(other,'prio',other)

	# def __eq__(self, other):
	# 	if isinstance(other,process):
	# 		return self.prio== other.prio
	# 	return NotImplemented

	# def __lt__(self, other):
	# 	if isinstance(other,process):
	# 		return self.prio<other.prio
	# 	return NotImplemented

	def __cmp__(self,other):
		return cmp(self.bt,other.bt)

def srt(plist,n):

	p=process()
	q=Q.PriorityQueue(maxsize=n)
	
	x=0 
	Pdone=0
	time_lap=0
	numer_completed=0
	templ=[]
	btl=dict()
	for y in plist:
		btl[y.pid]=y.bt
		pass
	print("in srt")
	while(1):
		
		print "this is  iteration number %d"%(x)
		if(x<n):
			print "going to push %d "%(x)
			
			while(plist[x].at<=time_lap):
				# print "pushed %d"%(x)
				q.put(plist[x])
				
				x+=1
				if(x>=n):
					break

			

		
		
		#print(q.empty())
		if(q.empty()==False):
			#time_lap+=1

			p=q.get()
			print "printing in q"
			p.disp()
			p.bt-=1
			time_lap+=1
			if(p.bt==0):
				p.ct=time_lap
				p.wat=time_lap-btl[p.pid]-p.at
				if p.wat<0:
					p.wat=0
					pass
				p.tat=p.ct-p.at
				p.bt=btl[p.pid]
				templ.append(p)
				Pdone+=1
			else:
				q.put(p)	

		else :
			time_lap+=1
		if(Pdone==n):
			break

	print "SRT schduling done !"
	return templ
	pass

def take_in(n):

	plist=[]
	
	for x in range(0,n):
			p=process()
			p.pid=x
			p.at=int(input())
			p.bt=int(input())
			
			plist.append(p)
			

	return plist

def take_out(plist,n):
	print "displaying"
	for x in range(0,n):
		plist[x].disp()
	pass

def AVG(plist,n):
	print "the Averages "
	sumt=0
	sumw=0
	for x in plist:
		sumt+=x.tat
		sumw+=x.wat
		pass

	print "The average TA time ",sumt/n
	print "the average WA Time ",sumw/n

def main():
	
	n=int(raw_input("enter the processes number"))
	plist=take_in(n)
	if not plist:
		print "List is empty"
	plist.sort(key=lambda process:process.at)
	print"Took in "
	take_out(plist,n)
	plist=srt(plist,n)

	take_out(plist,n)
	AVG(plist,n)
	pass



if __name__ == '__main__':
	main()