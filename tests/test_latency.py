import socket
import time
import math

HOST: str = "0.0.0.0"
PORT: int = 9152

lantency_history = []
times = []

for i in range(10000):
    times.append(time.time_ns() - time.time_ns())

f_callback_error = sum(times)/len(times) * -1e-6

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    for i in range(10000000):
        s.sendall(f'push {time.time_ns()}'.encode())
        data = s.recv(1024)
        s.sendall(b'pull')
        data = s.recv(1024)
        recived = time.time_ns()
        lantency_history.append(recived - int(data.decode().split(' ')[-1]))

    # Latência média, mínima e máxima
    lat_avg = sum(lantency_history) / len(lantency_history) * 1e-6
    lat_min = min(lantency_history) * 1e-6
    lat_max = max(lantency_history) * 1e-6

    # Percentis
    sorted_lantency = sorted(lantency_history)
    p90 = sorted_lantency[math.ceil(0.9 * len(sorted_lantency)) - 1] * 1e-6
    p99 = sorted_lantency[math.ceil(0.99 * len(sorted_lantency)) - 1] * 1e-6

    print(f"Latencia media  : {lat_avg:.6f} ms +- {f_callback_error:.6f}")
    print(f"Latencia minima : {lat_min:.6f} ms +- {f_callback_error:.6f}")
    print(f"Latencia maxima : {lat_max:.6f} ms +- {f_callback_error:.6f}")
    print(f"P90             : {p90:.6f} ms")
    print(f"P99             : {p99:.6f} ms")
