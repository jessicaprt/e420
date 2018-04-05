import pandas
from  matplotlib import pyplot
import matplotlib.pyplot as plt
import seaborn

EXECUTABLES = [ "main" ]
DATA_SIZES = [5155, 13000, 18789]
NODE_SIZES = [1001, 5424, 10000]
PROC_SIZES = [1, 4, 8, 16]
TOTAL_RUNS = 10
TEST_RESULTS_DIR = "test-results"
OUT_DIR = "stats"
output = []

def gen_graph(data, node_size):
    plt.figure()
    df2 = pandas.DataFrame(data, columns=EXECUTABLES)
    ax = df2.plot.bar()

    plt.title('Performance with {} nodes'.format(node_size), fontsize=12)
    plt.xlabel('Number of Processes', fontsize=12)
    plt.ylabel('Execution Time (s)', fontsize=12)
    ax.set_xticklabels(PROC_SIZES, fontsize=10)
    plt.savefig('./stats/{}-fig.png'.format(data_size))

for i in range(len(DATA_SIZES)):
    data_size = DATA_SIZES[i]
    node_size = NODE_SIZES[i]
    means = []
    for proc_size in PROC_SIZES:
        means.append([])
        for executable in EXECUTABLES:
            latency_file = "./{}/{}-{}-{}.txt".format(TEST_RESULTS_DIR, executable, data_size, proc_size)
            mean_latency = 0

            with open(latency_file) as file:
                data = [float(line.strip()) for line in file.readlines()]
                mean_latency = sum(data) / float(len(data))
                means[-1].append(mean_latency)
    print("Means for {}: {}".format(node_size, means))
    gen_graph(means, node_size)