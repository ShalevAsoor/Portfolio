import socket

def process_client_message(client_msg):
    """
    Process the client message to extract genre and date information.
    Returns genre, date1, date2, and flags indicating any errors.
    """
    genreError = False
    dateError = False
    
    # Splits the message to get the genre
    genreFix = client_msg.split(":")[1]
    genre = genreFix.strip().lower()
    
    # Sets the genreError flag to true if there is a problem with the genre
    if genre not in genreList:
        genreError = True
    
    # Splits the message to get the years
    dateFix = client_msg.split("&")[1].split(':')[1].split('-')
    date1 = int(dateFix[0].strip())
    date2 = int(dateFix[1].strip())

    # Sets the dateError flag to true if there is a problem with the date
    if date1 > date2:
        dateError = True
    
    return genre, date1, date2, genreError, dateError

def fix_movie_data(server_msg):
    """
    Fixes the movie data received from the server.
    Changes the name of the movies to "Proxy" and fixes the image URL.
    """
    splitted_msg = server_msg.split("&")
    splitted_msg[0] = 'MOVIEDATA#name:"Proxy"'
    
    imageFix = splitted_msg[7]
    imageFix = imageFix[:-4] + '.' + imageFix[-4:]
    splitted_msg[7] = imageFix
    
    server_msg = '&'.join(splitted_msg)
    return server_msg

def send_error_message(client_soc, error_message):
    """
    Sends an error message to the client socket.
    """
    server_msg = 'ERROR#"{}"'.format(error_message)
    client_soc.sendall(server_msg.encode())

def main():
    SERVER_IP = "54.71.128.194"
    SERVER_PORT = 92
    LISTEN_PORT = 9090
    genreList = ["action", "adventure", "animation", "biography", "comedy", "crime", "drama", "family", "fantasy",
                 "history", "horror", "music", "musical", "mystery", "romance", "sci-fi", "sport", "thriller", "war", "western"]
    
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as listening_sock:
        server_address = ('', LISTEN_PORT)
        listening_sock.bind(server_address)
        listening_sock.listen(1)
        
        client_soc, client_address = listening_sock.accept()
        client_msg = client_soc.recv(1024).decode()
        
        genre, date1, date2, genreError, dateError = process_client_message(client_msg)
        
        if not genreError and not dateError:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
                server_address = (SERVER_IP, SERVER_PORT)
                sock.connect(server_address)
        
                sock.sendall(client_msg.encode())
                server_msg = sock.recv(1024).decode()
                
                if "ERROR" not in server_msg:
                    if france:
                        send_error_message(client_soc, "France is banned!")
                    else:
                        server_msg = fix_movie_data(server_msg)
                        client_soc.sendall(server_msg.encode())
                else:
                    send_error_message(client_soc, server_msg)
        else:
            if dateError:
                send_error_message(client_soc, "Invalid years!")
            elif genreError:
                send_error_message(client_soc, "Invalid genre!")
    
    # Close the client socket and continue the loop or exit the program based on the condition
    client_soc.close()
    # ...
    # Continue with the rest of the code
    
if __name__ == '__main__':
    main()
