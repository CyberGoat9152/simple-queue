import socket

HOST: str = "0.0.0.0"
PORT: int = 9152

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok EMPTY\n"
    s.sendall(b'push 10;broker_1;id')
    data = s.recv(1024)
    s.sendall(b'push 20;broker_1;id')
    data = s.recv(1024)
    s.sendall(b'push 30;broker_1;id')
    data = s.recv(1024)
    s.sendall(b'push 40;broker_1;id')
    data = s.recv(1024)
    s.sendall(b'push 50;broker_1;id')
    data = s.recv(1024)
    s.sendall(b'push 60;broker_1;id')
    data = s.recv(1024)
    s.sendall(b'push 70;broker_1;id')
    data = s.recv(1024)
    s.sendall(b'push 80;broker_1;id')
    data = s.recv(1024)
    s.sendall(b'push 90;broker_1;id')
    data = s.recv(1024)
    s.sendall(b'push 42;broker_1;id')
    data = s.recv(1024)
    s.sendall(b'push 00;broker_1;id')
    data = s.recv(1024)
    assert data == b"-err FULL\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 10;broker_1;id\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 20;broker_1;id\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 30;broker_1;id\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 40;broker_1;id\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 50;broker_1;id\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 60;broker_1;id\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 70;broker_1;id\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 80;broker_1;id\n"
    s.sendall(b'pull')
    data = s.recv(1024)
    assert data == b"+ok 90;broker_1;id\n"

    