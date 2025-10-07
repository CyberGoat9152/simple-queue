import socket

HOST: str = "0.0.0.0"
PORT: int = 9152

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok EMPTY\n"
    s.sendall(b'push ;10')
    data = s.recv(1024)
    s.sendall(b'push ;20')
    data = s.recv(1024)
    s.sendall(b'push ;30')
    data = s.recv(1024)
    s.sendall(b'push ;40')
    data = s.recv(1024)
    s.sendall(b'push ;50')
    data = s.recv(1024)
    s.sendall(b'push ;60')
    data = s.recv(1024)
    s.sendall(b'push ;70')
    data = s.recv(1024)
    s.sendall(b'push ;80')
    data = s.recv(1024)
    s.sendall(b'push ;90')
    data = s.recv(1024)
    s.sendall(b'push ;42')
    data = s.recv(1024)
    s.sendall(b'push ;00')
    data = s.recv(1024)
    assert data == b"-err FULL\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 10\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 20\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 30\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 40\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 50\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 60\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 70\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 80\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 90\n"

    