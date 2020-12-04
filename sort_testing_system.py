from random import randint
import os
import subprocess

isPassed = True
sort_name = input("Please write your testing file name\n")
times = []
subprocess.run(["gcc", os.getcwd()+"\\"+ sort_name + "\\" + sort_name +".c", "-o" , os.getcwd()+"\\"+ sort_name + "\\" + sort_name + ".exe"])

for i in range(100):
    print("Generating input%d file..." %(i+1))
    arrLen = 10*(i+1)
    array = [randint(-10**4, 10**4) for j in range(arrLen)]
    fin = open("input%d.txt" %(i+1), "w")
    fin.write(str(arrLen) + "\n" + "\n".join(map(str, array)))
    fin.close()
    
    print("Running your programm")
    programm = subprocess.run([os.getcwd()+"\\"+ sort_name + "\\" + sort_name +".exe", "input%d.txt" %(i+1), "output%d.txt" %(i+1)])
    if programm.returncode != 0:
        print("Test %d - returncode = " %(i+1) + str(programm.returncode) + "\nYou can see input file in " + sort_name + " folder")
        isPassed = False
        break
		    
    fout = open("output%d.txt" %(i+1), "r")
    times.append(int(fout.readline()))
    new_arr = list(map(int, fout.readlines()))
    if sorted(array) != new_arr:
        print("Test %d - WA\nYou can see input and output files in " %(i+1) + sort_name + " folder")
        isPassed = False
        break
    print("Test %d passed" %(i+1))
    fout.close()
    os.remove("input%d.txt" %(i+1))
    os.remove("output%d.txt" %(i+1))
    os.system('cls')

if isPassed == True:
    print("All tests passed\n")
    print("Array length\tSort time (µs)")
    for i in range(100):
        print(10*(i+1), times[i], sep = '\t\t')
input("Please press Enter to close window... ")