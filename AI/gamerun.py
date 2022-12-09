import os
import subprocess

def runGame(mapfile, movefile):
    for filename in os.listdir(os.getcwd()):
        print(filename)
        proc = subprocess.Popen(["./a.out", mapfile, movefile, filename])
        proc.wait()