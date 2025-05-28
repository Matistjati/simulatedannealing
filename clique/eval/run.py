import subprocess
import random
from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path
import math

def evaluate_tc(args, inp,thi,tlo):
    full_input = f"{inp}\n{thi}\n{tlo}"
    try:
        res = subprocess.check_output(args, input=full_input.encode())
        return thi, tlo, res.decode().strip()
    except subprocess.CalledProcessError as e:
        print(f" ERROR: {e}")
    except subprocess.TimeoutExpired:
        print(f" TIMEOUT")

if __name__ == "__main__":
    dirname = "delete"
    dir = Path(dirname)
    data_dir = Path("..") / "data" / "g7.txt"
    with open(data_dir, "r") as f:
        inp = f.read()
    args = [f"./{dir}/bitset"]

    num_runs = 10000
    futures = []

    with ProcessPoolExecutor(3) as executor, open(dir / "res.txt", "a") as outf:
        for _ in range(num_runs):
            tlo = math.exp(random.uniform(-14, 14))
            thi = math.exp(random.uniform(-14, 14))
            if tlo > thi:
                tlo,thi=thi,tlo
            futures.append(
                executor.submit(evaluate_tc, args, inp,thi,tlo)
            )

        it = 0
        for future in as_completed(futures):
            it += 1
            print(f"Completed {it}/{num_runs}")
            thi, tlo, result = future.result()
            outf.write(f"{tlo} {thi} {result}\n")
            outf.flush()
