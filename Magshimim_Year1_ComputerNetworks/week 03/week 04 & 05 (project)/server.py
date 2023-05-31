from http import client
from operator import truediv
import socket
from time import sleep
import sys
import hashlib
import data

LISTEN_PORT = 8791

RESPONSE_FOR_1 = "Album list"
RESPONSE_FOR_2 = "List of song in an album"
RESPONSE_FOR_3 = "Songs length"
RESPONSE_FOR_4 = "Songs lyrics"
RESPONSE_FOR_5 = "What album is the song from"
RESPONSE_FOR_6 = "Song search (by name)"
RESPONSE_FOR_7 = "Song search (by lyrics)"
RESPONSE_FOR_8 = "Exit"
RESPONSE_FOR_ERROR = "An error has occurred, please try again"
RESPONSE_FOR_ILLEGAL_INPUT = "Illegal input, please try again!"
ILLEGAL_CODE = "0 | "
VALID_CODE = "10 | "
DOTS = "..."

exit = True  # Flag to control server exit
test = 0  # Counter for testing purposes
temp = []  # Temporary variable for storing server responses

def login(password):
    '''
    This function encrypts the password and checks if it matches the one saved in the constant.
    '''

    password = hashlib.md5(password.encode('utf-8')).hexdigest()

    return password == ENCODED_PASSWORD

def choice(request, albums, div_msg, e_msg):
    """
    This function checks which response the server should send to the client
    or if the server should send an error.
    """

    temp = []

    if "1" in div_msg[0] and "|" in e_msg:
        temp = data.one(albums)
    elif "2" in div_msg[0] and "|" in e_msg:
        temp = data.two(albums, request)
    elif "3" in div_msg[0] and "|" in e_msg:
        temp = data.three(albums, request)
    elif "4" in div_msg[0] and "|" in e_msg:
        temp = data.four(albums, request)
    elif "5" in div_msg[0] and "|" in e_msg:
        temp = data.five(albums, request)
    elif "6" in div_msg[0] and "|" in e_msg:
        temp = data.six(albums, request)
    elif "7" in div_msg[0] and "|" in e_msg:
        temp = data.seven(albums, request)
    elif "8" in div_msg[0] and "|" in e_msg:
        temp = "ERROR"
    else:
        msg = ILLEGAL_CODE + RESPONSE_FOR_ILLEGAL_INPUT

    return temp

def main():
    exit = True
    test = 0
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as listening_sock:
        server_address = ('', LISTEN_PORT)
        listening_sock.bind(server_address)

        listening_sock.listen(1)
        while True:
            if test == 0:
                print("Waiting for connection", end='')

                for x in DOTS:  # Waiting for connection animation
                    print(x, end='')
                    sys.stdout.flush()
                    sleep(0.7)
            client_soc, client_address = listening_sock.accept()
            try:
                client_soc.sendall("Please enter your password: ".encode())
                client_msg = client_soc.recv(1024)
                client_msg = client_msg.decode()

                login(client_msg)

                while login(client_msg) == False:
                    client_soc.sendall(
                        "Wrong password, please try again: ".encode())
                    client_msg = client_soc.recv(1024)
                    client_msg = client_msg.decode()
                    login(client_msg)
                client_soc.sendall("Correct password".encode())
                albums = data.pinkFloyd()
            except Exception as error:
                print(error)
            if test == 0:
                client_soc.sendall(
                    "Connection established! Welcome".encode())  # Sends a welcome message
                print("\nConnection established!" + str(client_address))

            test += 1
            try:
                while True:
                    client_msg = client_soc.recv(1024)
                    client_msg = client_msg.decode()

                    # If the client forces disconnection, the server won't crash, it will wait for a new connection
                    if len(client_msg) == 0 or exit == False:
                        print(str(client_address) + " DISCONNECTED!")
                        break

                    # Splits the message to check for a number
                    div_msg = client_msg.split(" | ")

                    temp = choice(div_msg[1], albums, div_msg[0], client_msg)

                    if div_msg[0] == "1":
                        temp = ', '.join(temp)

                    client_soc.sendall(temp.encode())
            except Exception as error:
                print(error)
            test = 0

if __name__ == "__main__":
    main()
