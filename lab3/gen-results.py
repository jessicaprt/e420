import subprocess, time
import os.path
from pathlib import Path


EXECUTABLES = [
    "original",
    "shared_parallel_guided"
]

OUT_DIR = "test-results"
DATA_GEN = "datagen"

TOTAL_RUNS = 100
THREAD_SIZE = [1, 4, 16]

def start_command(command):
    return subprocess.Popen(['bash','-c', command])

def exec_command(command):
    start_command(command).wait()

exec_command("rm {0}/*".format(OUT_DIR))
exec_command("mkdir {0}".format(OUT_DIR))

if (not os.path.exists("data_input")):
    exec_command("./datagen -s 1024")

for executable in EXECUTABLES:
    for thread_size in THREAD_SIZE:
        print("Testing {} with a thread size of {}.".format(executable, thread_size))

        for i in range(TOTAL_RUNS):
            results_file = "./{0}/{1}-{2}.txt".format(OUT_DIR, executable, thread_size)
            launch_command = "./{}.out {} | tail -n 1 >> {}".format(executable, thread_size, results_file)
            process = exec_command(launch_command)