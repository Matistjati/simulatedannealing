import subprocess
import random
from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path
import math

def evaluate_tc(args, inp,tstart,tend):
    full_input = f"{inp}\n{tstart}\n{tend}"
    try:
        res = subprocess.check_output(args, input=full_input.encode())
        return tend, tstart, res.decode().strip()
    except subprocess.CalledProcessError as e:
        print(f" ERROR: {e}")
    except subprocess.TimeoutExpired:
        print(f" TIMEOUT")

if __name__ == "__main__":
    dirname = "v1"
    dir = Path(dirname)
    data_dir = Path("in.txt")
    with open(data_dir, "r") as f:
        inp = f.read()
    args = [f"./{dir}/sol"]

    num_runs = 10000
    futures = []

    with ProcessPoolExecutor(3) as executor, open(dir / "res.txt", "a") as outf:
        for _ in range(num_runs):
            tstart = math.exp(random.uniform(-14, 14))
            tend = math.exp(random.uniform(-14, 14))
            if tstart < tend:
                tstart,tend=tend,tstart
            futures.append(
                executor.submit(evaluate_tc, args, inp,tstart,tend)
            )

        it = 0
        for future in as_completed(futures):
            it += 1
            print(f"Completed {it}/{num_runs}")
            tend, tstart, result = future.result()
            outf.write(f"{tend} {tstart} {result}\n")
            outf.flush()
