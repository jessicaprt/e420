import pandas
from  matplotlib import pyplot
import matplotlib.pyplot as plt
import seaborn

EXECUTABLES = [
    "original",
    "shared_parallel_static",
    "shared_parallel_dynamic",
    "shared_parallel_guided"
]

THREAD_SIZES = [1, 4, 16]
TOTAL_RUNS = 10
TEST_RESULTS_DIR = "test-results"
OUT_DIR = "stats"
output = []

def gen_client_graph(server_executable, array_size, data):
    seaborn.set(style='ticks')

    plot = seaborn.distplot(data, color='r', hist_kws=dict(cumulative=True), kde_kws=dict(cumulative=True))
    figure = plot.get_figure()

    figure.suptitle("{} with an array size of {}".format(server_executable, array_size), fontsize = 16)

    axis = figure.gca()
    axis.set_autoscale_on(False)
    axis.axis([0, 0.4, 0, 1.1])

    plt.xlabel('Client Latency (ms)', fontsize=12)
    plt.ylabel('Cumulative Probability', fontsize=12)

    figure.savefig("./{}/{}-client-{}.png".format(OUT_DIR, server_executable, array_size), dpi=400)
    figure.clf()

def gen_server_graph(server_executable, array_size, data):
    seaborn.set(style='ticks')

    plot = seaborn.distplot(data, color='g' ,hist_kws=dict(cumulative=True), kde_kws=dict(cumulative=True))
    figure = plot.get_figure()

    figure.suptitle("{} with an array size of {}".format(server_executable, array_size), fontsize = 16)

    axis = figure.gca()
    axis.set_autoscale_on(False)
    axis.axis([0, 0.035, 0, 1.1])

    plt.xlabel('Server Memory Access Latency (ms)', fontsize=12)
    plt.ylabel('Cumulative Probability', fontsize=12)

    figure.savefig("./{}/{}-server-{}.png".format(OUT_DIR, server_executable, array_size), dpi=400)
    figure.clf()

def gen_graph(data):
    df2 = pd.DataFrame(np.random.rand(10, 4), columns=['a', 'b', 'c', 'd'])
    df2.plot.bar()


means = []
for thread_size in enumerate(THREAD_SIZES):
    means.append([])
    for executable in EXECUTABLES:
        latency_file = "./{}/{}-{}.txt".format(TEST_RESULTS_DIR, executable, thread_size)
        mean_latency = 0

        with open(latency_file) as file:
            data = [float(line.strip()) for line in file.readlines() if float(line.strip()) < 1]
            mean_latency = sum(client_data) / float(len(client_data))
            means[-1].append(mean_latency)

gen_graph(data)


with open("./{}/summary.txt".format(OUT_DIR), 'w') as summary_file:
    for line in output:
        summary_file.write(line + "\n")