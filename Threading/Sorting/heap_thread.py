import threading


def heapify(arr, n, i): 
    largest = i # Initialize largest as root 
    l = 2 * i + 1     # left = 2*i + 1 
    r = 2 * i + 2     # right = 2*i + 2 
  
    # See if left child of root exists and is 
    # greater than root 
    if l < n and arr[i] < arr[l]: 
        largest = l 
  
    # See if right child of root exists and is 
    # greater than root 
    if r < n and arr[largest] < arr[r]: 
        largest = r

    threads=[]
  
    # Change root, if needed 
    if largest != i: 
        arr[i],arr[largest] = arr[largest],arr[i] # swap 
  
        threads.append(threading.Thread(target=heapify,args=(arr, n, largest)))
        threads[-1].start()

        for x in threads:
        	x.join()
        	pass


        


def heapSort(arr): 
    n = len(arr)
    threads=[] 
    # Build a maxheap. 
    for i in range(n, -1, -1): 
        threads.append(threading.Thread(target=heapify,args=(arr, n, i)))
        threads[-1].start()

    for x in threads:
    	x.join()

    threads=[]

    for i in range(n-1, 0, -1): 
        arr[i], arr[0] = arr[0], arr[i]
        # threads.append(threading.Thread(target=heapify,args=(arr, i, 0)))
        # threads[-1].start()

    # for x in threads:
    # 	x.join()
    # 	pass
        heapify(arr, i, 0)

def main():

	

	# n=int(input("Enter the size of the array"))

	print("Enter the elements of the array")

	arr=[]

	for x in input().split():
		arr.append(int(x))

	print("this is the array")

	print(arr)

	heapSort(arr)

	print("this is the sorted array")

	print(arr)





if __name__ == '__main__':
	main()
