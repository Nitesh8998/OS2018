class process(object):
	at=None
	bt=None
	ct=0
	tat=None
	wat=0
	pid=None
	

	def disp(self):
		print("%d %d  %d %d %d %d"%(self.pid,self.at,self.bt,self.ct,self.tat,self.wat))	

			


class sjf(object):
	
	
	plist=[]
	

	def __init__(self):
		self.n = int(input("Enter the number of process"))
		for x in range(0,self.n):
			p=process()
			p.pid=x
			p.at=int(input())
			p.bt=int(input())
			self.plist.append(p)


			pass

	def scheduler(self):
		schedule=[]
		self.plist.sort(key=lambda process:process.at)
		#self.printer()
		prev=0
		self.plist[0].ct=prev+self.plist[0].bt
		prev=self.plist[0].ct
		self.plist[0].tat=self.plist[0].ct-self.plist[0].at
		#self.plist[0].wat=self.plist[0].tat-self.plist[0].bt
		if(self.plist[0].ct<self.plist[1].at ):
				self.plist[1].ct=self.plist[1].at-self.plist[0].ct
			
		for x in range(1,self.n):
			
			j=x
			p=process()
			p.bt=99
			#print(" out %d prev %d" %(j,prev) )
			while(self.plist[j].at<=prev):
				#print(" in %d" %(j) )
				if(p.bt>self.plist[j].bt):
					#print("swapped")
					p=self.plist[j]
					pos=j
					
				print("%d %d"%(p.bt,p.pid))
				
				j=j+1
				if(j>=self.n):
					break
			pass
			if(p.bt!=99):
					
				self.plist[pos]=self.plist[x]
				self.plist[x]=p

			
			self.plist[x].ct+=prev+self.plist[x].bt
			if(x+1!=self.n and self.plist[x].ct<self.plist[x+1].at ):
				self.plist[x+1].ct=self.plist[x+1].at-self.plist[x].ct	
			self.plist[x].tat=self.plist[x].ct-self.plist[x].at
			
			
			prev=self.plist[x].ct


		sum=0
		for x in range(0,self.n):
			self.plist[x].wat+=self.plist[x].tat-self.plist[x].bt
			if(x+1!=self.n and self.plist[x].ct<self.plist[x+1].at ):

				sum+=self.plist[x+1].at-self.plist[x].ct
				self.plist[x+1].wat=self.plist[x+1].at-self.plist[x].ct
				

			sum+=self.plist[x].wat
			pass

		
		print(sum)
		print("The wating total wating time={0} and the avg wating time ={1}".format(sum,sum/self.n))

		pass

	def printer(self):
		print("printing")
		for x in self.plist:
			x.disp()
		

def main():
	s=sjf()

	s.scheduler()
	s.printer()



if __name__ == '__main__':
	main()