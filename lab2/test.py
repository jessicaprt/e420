import subprocess, time

SERVER_EXECUTABLES = [
    "server_single_mutex",
    "server_multiple_mutex",
    "server_single_rwlock",
    "server_multiple_rwlock"
]

OUT_DIR = "test-results"
CLIENT_EXECUTABLE = "client"

TOTAL_RUNS = 115
SERVER_PORT = 3000
ARRAY_SIZES = [10, 100, 1000, 10000]

def start_command(command):
    return subprocess.Popen(['bash','-c', command])

def exec_command(command):
    start_command(command).wait()

exec_command("rm {0}/*".format(OUT_DIR))
exec_command("mkdir {0}".format(OUT_DIR))

for server_executable in SERVER_EXECUTABLES:
    for array_size in ARRAY_SIZES:
        print("Testing {} with an array size of {}.".format(server_executable, array_size))

        for i in range(TOTAL_RUNS):
            server_results_file = "./{0}/{1}-server-{2}.txt".format(OUT_DIR, server_executable, array_size)
            server_launch_command = "./{}.out {} {} | tail -n 1 >> {}".format(server_executable, SERVER_PORT, array_size, server_results_file)
            server_process = start_command(server_launch_command)
            time.sleep(0.2)

            client_results_file = "./{0}/{1}-client-{2}.txt".format(OUT_DIR, server_executable, array_size)
            client_command = "./{} {} {} | tail -n 1 >> {}".format(CLIENT_EXECUTABLE, SERVER_PORT, array_size, client_results_file)
            client_process = start_command(client_command)

            client_process.wait()
            server_process.wait()
            SERVER_PORT += 1
            time.sleep(0.1)