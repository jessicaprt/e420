import subprocess, time
import os.path

OUT_DIR = "test-results"
EXECUTABLE = "main"
DATA_GEN = "datatrim"

TOTAL_RUNS = 10
THREAD_SIZE = [1, 4, 8, 16]
DATA_SIZES = [4000, 8000, 16000]

def start_command(command):
    return subprocess.Popen(['bash','-c', command])

def exec_command(command):
    start_command(command).wait()

exec_command("rm {0}/*".format(OUT_DIR))
exec_command("mkdir {0}".format(OUT_DIR))

if (not os.path.exists("data_input")):
    exec_command("./{} -s {}".format(DATA_GEN, DATA_SIZES))

for data_size in DATA_SIZES:
    print("Testing {} with a thread size of {}.".format(EXECUTABLE, data_size))
    print("Generating data with size of {}".format(DATA_SIZES))
    exec_command("./{} -s {}".format(DATA_GEN, DATA_SIZES))
    for i in range(TOTAL_RUNS):
        results_file = "./{0}/{1}-{2}.txt".format(OUT_DIR, EXECUTABLE, data_size)
        launch_command = "mpirun -np {} ./{} | tail -n 1 >> {}".format(data_size, EXECUTABLE, results_file)
        process = exec_command(launch_command)