from http import client
from operator import truediv
import socket
from tkinter import EXCEPTION
from unittest import expectedFailure

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8791
MENU = "MENU:\n 1 - Album list \n 2 - List of song in an album \n 3 - Songs length \n 4 - Songs lyrics \n 5 - What album is the song from \n 6 - Song search (by name) \n 7 - Song search (by lyrics) \n 8 - EXIT \n"


def messageCheck(msg):
    """
    Checks if the message contains the termination command to close the connection.

    Args:
        msg (str): The message received from the server.

    Returns:
        bool: True if the message contains the termination command, False otherwise.
    """
    if " | " in msg:
        t_msg = msg.split(" | ")
        # Closes the connection from the client's side (does not crash the server, it will look for a new connection)
        if "8" in t_msg[0]:
            return True
    return False


def main():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            server_address = (SERVER_IP, SERVER_PORT)
            sock.connect(server_address)

            server_msg = sock.recv(1024)
            server_msg = server_msg.decode()
            print(server_msg)

            password = input()
            sock.sendall(password.encode())
            server_msg = sock.recv(1024)
            server_msg = server_msg.decode()
            print(server_msg)

            while server_msg == "wrong password please try again: ":

                password = input()
                sock.sendall(password.encode())
                server_msg = sock.recv(1024)
                server_msg = server_msg.decode()

                if server_msg == "wrong password please try again: ":
                    print(server_msg)

            print(MENU)

            while True:
                server_msg = sock.recv(1024)
                server_msg = server_msg.decode()
                print(server_msg)

                msg1 = input("Please enter a message (number (1-8)): ")
                msg2 = ""
                msg = ""

                if msg1 == "2":
                    msg2 = input("Please enter the album's name: ")

                elif msg1 == "3":
                    msg2 = input("Please enter the song's name: ")

                elif msg1 == "4":
                    msg2 = input("Please enter the song's name: ")

                elif msg1 == "5":
                    msg2 = input("Please enter the song's name: ")

                elif msg1 == "6":
                    msg2 = input("Please enter the word: ")

                elif msg1 == "7":
                    msg2 = input("Please enter the word: ")
                else:
                    msg2 = "ERROR"

                msg = msg1 + " | " + msg2

                if messageCheck(msg):
                    break
                sock.sendall(msg.encode())
    except Exception as error:
        print(error)


if __name__ == "__main__":
    main()
