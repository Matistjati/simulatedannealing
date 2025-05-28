import subprocess
import random
from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path
import math

def evaluate_tc(args, tlo, thi, inp, ans):
    full_input = f"{inp}\n{thi}\n{tlo}\n{ans}"
    try:
        res = subprocess.check_output(args, input=full_input.encode())
        return res.decode().strip()
    except subprocess.CalledProcessError as e:
        return f"{thi} {tlo} ERROR: {e}"
    except subprocess.TimeoutExpired:
        return f"{thi} {tlo} TIMEOUT"

def run_test(args, tlo, thi, data_dir):
    for file in Path(data_dir).glob("*.in"):
        with open(file, "r") as f:
            inp = f.read()
        with open(Path(file.with_suffix(".ans")), "r") as f:
            ans = f.read()
        res = evaluate_tc(args, tlo, thi, inp, ans)
        try:
            if int(res) != int(ans):
                return tlo, thi, 0
        except ValueError:
            return tlo, thi, 0  # if result can't be parsed
    return tlo, thi, 1

def generate_params():
    tlo = math.exp(random.uniform(-20, 20))
    thi = math.exp(random.uniform(-20, 20))
    if tlo > thi:
        tlo, thi = thi, tlo
    return tlo, thi

if __name__ == "__main__":
    problem = Path("piano")
    data = problem / "data"
    args = [f"./{problem}/a.out"]

    num_runs = 5000
    futures = []

    with ProcessPoolExecutor(3) as executor, open("res.txt", "a") as outf:
        for _ in range(num_runs):
            tlo, thi = generate_params()
            futures.append(
                executor.submit(run_test, args, tlo, thi, str(data))
            )

        it = 0
        for future in as_completed(futures):
            it += 1
            print(f"Completed {it}/{num_runs}")
            tlo, thi, result = future.result()
            outf.write(f"{tlo} {thi} {result}\n")
            outf.flush()
