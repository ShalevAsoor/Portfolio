from scapy.all import *
import hashlib

port = ""
code = ""
SERVERIP = "54.71.128.194"
SERVERPORT = 99
MSGPART1 = "location_md5="
MSGPART2 = ",airport=nevada25.84,time=15:52,lane=earth.jup,vehicle=2554,fly"


def ip_check(packet):
    """
    This function only returns a packet if it was sent from the Alien server IP.
    """
    if IP in packet:
        if packet[IP].src == SERVERIP:
            return Raw in packet


def ip_print(packet):
    """
    This function receives a packet, decrypts it, and prints it.
    """
    global code

    p = packet[Raw].load.decode()

    pData = p[6:]
    key = int(p[3:6])
    decMsg = ""
    decMsg = cypher(26 - key, pData)

    if 'location data' in decMsg:  # Checks if the message contains a location code.
        # Adding the part of the location data to the entire code string.
        code += decMsg[-10:]
        print(decMsg)


def cypher(key, text):
    """
    This function decrypts a message with the Alien format.
    """
    decoded = ""
    c = 0

    for i in range(len(text)):
        char = text[i]
        c = c + 1

        if c % 2 == 1:
            if char.isupper():
                decoded += chr((ord(char) + key - 65) % 26 + 65)
            elif char.islower():
                decoded += chr((ord(char) + key - 97) % 26 + 97)
            else:
                decoded += char
        else:
            decoded += char
    return decoded


def stop_filter(packet):
    """
    Stops sniffing if we sniffed the last part of the location data.
    """
    global port
    if IP in packet and packet[IP].src == SERVERIP and "10/10" in packet[Raw].load.decode():
        # Getting the port that was used in the socket with the Alien Server.
        # Getting the port that was opened on our side so we could send a message back to the server.
        port = packet[UDP].dport
        return True
    return False


def main():
    packets = sniff(lfilter=ip_check, prn=ip_print, stop_filter=stop_filter)
    result = hashlib.md5(code.encode())
    flyMsg = f"FLY008" + cypher(8, MSGPART1 + result.hexdigest() + MSGPART2)

    print("message sent: " + flyMsg)

    msg = IP(dst=SERVERIP) / UDP(dport=SERVERPORT, sport=port) / Raw(load=flyMsg)

    sr1(msg, verbose=0)


if __name__ == "__main__":
    main()
