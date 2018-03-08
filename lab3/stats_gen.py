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

def gen_graph(data):
    print(data)
    plt.figure()
    df2 = pandas.DataFrame(data, columns=EXECUTABLES)
    ax = df2.plot.bar(xticks = THREAD_SIZES)

    plt.title('Performance of Different Parallelization Strategies', fontsize=12)
    plt.xlabel('Number of Threads', fontsize=12)
    plt.ylabel('Execution Time', fontsize=12)

    plt.savefig('./fig.png')


means = []
for thread_size in THREAD_SIZES:
    means.append([])
    for executable in EXECUTABLES:
        latency_file = "./{}/{}-{}.txt".format(TEST_RESULTS_DIR, executable, thread_size)
        mean_latency = 0

        with open(latency_file) as file:
            data = [float(line.strip()) for line in file.readlines()]
            mean_latency = sum(data) / float(len(data))
            means[-1].append(mean_latency)

gen_graph(means)