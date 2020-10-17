import sys, getopt, random

def main(argv):
    #Random quantum
    quantum = random.randint(2, 6)
    print("Random quantum is: ", quantum)
    context_switch = 2
    execution_time = 0
    avg_turnaround_tm= 0.0
    context_switchs=0
    processes=[]

    #Generate a list from random length
    for i in range(1, random.randint(4,8)):
	#Generate random procceses
        processes.append(random.randint(1,12))


    print("Processes: ", processes)
    num_processes = len(processes)

    try:
        opts, args= getopt.getopt(argv,"hq:",["quantum_time="])
    except getopt.GetoptError:
        print ("rrobin.py -q <quantum time>")
        sys.exit(-1)
    for opt, arg in opts:
        if opt == '-h':
            print ("test.py -q <quantum time>")
            sys.exit()
        elif opt in ("-q", "--quantum_time"):
            quantum = int(arg)

    for process in processes:
        if process <= quantum:
            print("process executed!")
            execution_time+=process
            print("execution time " + str(execution_time))
        else:
            print("process interrupted, exceeds quantum")
            remain_time = process - quantum
            context_switchs+=1
            print("time process executed: "+ str(quantum))
            execution_time+=quantum + context_switch
            print("executiom time " + str(execution_time))
            processes.append(remain_time)

        print(processes)
        print()

    avg_turnaround_tm = float(execution_time)/float(num_processes)
    print("Using a random quantum of: ", quantum)
    print("Total context switches: " + str(context_switchs))
    print("Avg turnaround time: " + str(avg_turnaround_tm))
    print("Switching cost: " + str(context_switch * context_switchs))

if __name__ == "__main__":
    main(sys.argv[1:])
