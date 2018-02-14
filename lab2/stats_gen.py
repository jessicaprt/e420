SERVER_EXECUTABLES = [
    "server_single_mutex",
    "server_multiple_mutex",
    "server_single_rwlock",
    "server_multiple_rwlock"
]

ARRAY_SIZES = [10, 100, 1000, 10000]
TOTAL_RUNS = 100
TEST_RESULTS_DIR = "test-results"
OUT_DIR = "stats"
output = []

for server_executable in SERVER_EXECUTABLES:
    for array_size in ARRAY_SIZES:
        client_latency_file = "./{}/{}-{}.txt".format(TEST_RESULTS_DIR, server_executable, array_size)
        sum = 0
        with open(client_latency_file) as client_file:
            for line in client_file:
                sum += float(line.strip())
        output.append("{}-{} mean = {} ms".format(server_executable, array_size, sum / float(TOTAL_RUNS)))

with open("./{}/summary.txt".format(OUT_DIR), 'w') as summary_file:
    for line in output:
        summary_file.write(line + "\n")