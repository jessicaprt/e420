import subprocess, time
import os.path

OUT_DIR = "test-results"
EXECUTABLE = "main"
DATA_GEN = "datatrim"

TOTAL_RUNS = 10
PROC_SIZES = [1, 4, 8, 16]
DATA_SIZES = [4000, 8000, 16000]

def start_command(command):
    return subprocess.Popen(['bash','-c', command])

def exec_command(command):
    start_command(command).wait()

exec_command("rm {0}/*".format(OUT_DIR))
exec_command("mkdir {0}".format(OUT_DIR))

for data_size in DATA_SIZES:
    print("Testing {} with a thread size of {}.".format(EXECUTABLE, data_size))
    print("Generating data with size of {}".format(DATA_SIZES))
    exec_command("./{} -b {}".format(DATA_GEN, data_size))
    for proc_size in PROC_SIZES:
        for i in range(TOTAL_RUNS):
            results_file = "./{0}/{1}-{2}-{3}.txt".format(OUT_DIR, EXECUTABLE, data_size, proc_size)
            launch_command = "mpirun -np {} ./{} | tail -n 1 >> {}".format(proc_size, EXECUTABLE, results_file)
            process = exec_command(launch_command)