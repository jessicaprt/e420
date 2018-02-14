import pandas
from  matplotlib import pyplot
import matplotlib.pyplot as plt
import seaborn

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

def gen_client_graph(server_executable, array_size, data):
    seaborn.set(style='ticks')

    plot = seaborn.distplot(data, hist_kws=dict(cumulative=True), kde_kws=dict(cumulative=True))
    figure = plot.get_figure()

    figure.suptitle("{} with an array size of {}".format(server_executable, array_size), fontsize = 16)
    plt.xlabel('Client Latency (ms)', fontsize=12)
    plt.ylabel('Cumulative Probability', fontsize=12)

    figure.savefig("./{}/{}-{}.png".format(OUT_DIR, server_executable, array_size), dpi=400)
    figure.clf()

for server_executable in SERVER_EXECUTABLES:
    for array_size in ARRAY_SIZES:
        client_latency_file = "./{}/{}-{}.txt".format(TEST_RESULTS_DIR, server_executable, array_size)
        mean = 0

        with open(client_latency_file) as client_file:
            client_data = [float(line.strip()) for line in client_file.readlines()]
            mean = sum(client_data) / float(len(client_data))
            gen_client_graph(server_executable, array_size, client_data)

        output.append("{}-{} mean = {} ms".format(server_executable, array_size, mean))

with open("./{}/summary.txt".format(OUT_DIR), 'w') as summary_file:
    for line in output:
        summary_file.write(line + "\n")