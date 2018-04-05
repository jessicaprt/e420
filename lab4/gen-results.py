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
    exec_command("./datagen -s 2048")


for data_size in DATA_SIZES:
    print("Testing {} with a thread size of {}.".format(EXECUTABLE, data_size))

    for i in range(TOTAL_RUNS):
        results_file = "./{0}/{1}-{2}.txt".format(OUT_DIR, executable, thread_size)
        launch_command = "./{}.out {} | tail -n 1 >> {}".format(executable, thread_size, results_file)
        process = exec_command(launch_command)