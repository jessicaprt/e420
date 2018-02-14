import subprocess, time

SERVER_EXECUTABLES = [
    "server_single_mutex",
    "server_multiple_mutex",
    "server_single_rwlock",
    "server_multiple_mutex"
]

OUT_DIR = "test-results"
CLIENT_EXECUTABLE = "client"

TOTAL_RUNS = 100
SERVER_PORT = 3000
ARRAY_SIZES = [10, 100, 1000, 10000]

def start_command(command):
    return subprocess.Popen(['bash','-c', command])

def exec_command(command):
    start_command(command).wait()

exec_command("mkdir -p {0}".format(OUT_DIR))

for server_executable in SERVER_EXECUTABLES:
    for array_size in ARRAY_SIZES:
        for i in range(TOTAL_RUNS):
            server_launch_command = "./{}.out {}".format(server_executable, array_size)
            server_process = start_command(server_launch_command)

            results_file = "./{0}/{1}-{2}.txt".format(OUT_DIR, server_executable, array_size)
            client_command = "./{} {} {} | tail -n 1 >> {}".format(CLIENT_EXECUTABLE, SERVER_PORT, array_size, results_file)
            client_process = start_command(client_command)

            client_process.wait()
            server_process.wait()