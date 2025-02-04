import os
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

df = pd.read_csv("results/log.csv")

plot_dir = Path("Plots")
os.makedirs(plot_dir, exist_ok=True)

# Plot speedup for number of threads vs. data size
for solver in ["TreeStructuredSum", "GlobalSum"]:
    fig, ax = plt.subplots()

    labels = []

    base_mask = [
        name == "SerialSum" and threads == 1
        for name, threads in zip(df["Name"], df["Threads"])
    ]

    threads = df["Threads"].unique()

    for thread in threads:

        mask = [
            name == solver and threads == thread
            for name, threads in zip(df["Name"], df["Threads"])
        ]

        x = df[mask]["Size"]
        y_s = df[base_mask]["Mean"].div(df[mask]["Mean"].values)
        y_min_s = df[base_mask]["Mean"].div(df[mask]["Min"].values)
        y_max_s = df[base_mask]["Mean"].div(df[mask]["Max"].values)

        y_l_err_s = abs(y_s - y_min_s)
        y_u_err_s = abs(y_s - y_max_s)
        y_2_sided_err_s = [y_l_err_s, y_u_err_s]

        # ax.errorbar(x, y_s, y_2_sided_err_s, capsize=5)
        ax.plot(x, y_s)

        labels.append(f"{thread} Threads")

    ax.set_xscale("log")
    ax.set_xlabel("Dataset Size (Number of Floats)")
    ax.set_ylabel("Speedup")
    ax.set_ylim((1, 10))
    ax.set_title(f"{solver} Speedup Proportional to SerialSum")
    ax.legend(labels, loc="upper left")
    ax.grid(True)
    fig.show()
    fig.savefig(plot_dir / f"{solver}.png", dpi=600)

# Plot speedup for each thread for 1e9 iterations
for solver in ["TreeStructuredSum", "GlobalSum"]:
    fig, ax = plt.subplots()

    labels = []

    base_mask = [
        name == "SerialSum" and threads == 1 and size == np.int64(1000000000)
        for name, threads, size in zip(df["Name"], df["Threads"], df["Size"])
    ]

    threads = df["Threads"].unique()

    for thread in threads:

        mask = [
            name == solver and threads == thread and size == np.int64(1000000000)
            for name, threads, size in zip(df["Name"], df["Threads"], df["Size"])
        ]

        x = df[mask]["Threads"]
        y_s = df[base_mask]["Mean"].div(df[mask]["Mean"].values)
        y_min_s = df[base_mask]["Mean"].div(df[mask]["Min"].values)
        y_max_s = df[base_mask]["Mean"].div(df[mask]["Max"].values)

        y_l_err_s = abs(y_s - y_min_s)
        y_u_err_s = abs(y_s - y_max_s)
        y_2_sided_err_s = [y_l_err_s, y_u_err_s]

        ax.errorbar(x, y_s, y_2_sided_err_s, capsize=5, fmt="o", ms=3, elinewidth=1)
        # ax.plot(x, y_s, 'o')

        labels.append(f"{thread} Threads")

    ax.set_xlabel("Number of threads")
    ax.set_ylabel("Speedup")
    ax.set_ylim((1, 10))
    ax.set_title(f"{solver} Speedup Proportional to SerialSum")
    ax.legend(labels, loc="lower right")
    ax.grid(True)
    fig.show()
    fig.savefig(plot_dir / f"{solver}_1e9_elements.png", dpi=600)
