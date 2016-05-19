import socket
import sys
import os
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
IP = '192.168.240.1'
PORT = 123
server_address = (IP, PORT)

sock.bind(server_address)

#print 'Starting server up on %s port %s' % sock.getsockname()

sock.listen(1)

#print 'YUN SERVER: Waiting for a connection'
connection, client_address = sock.accept()
log =  'YUN SERVER: Client connected:' + str(tuple(client_address))
messagedata=""
os.system('echo \'<==========- Start connection -==========>\' >> log.txt')
os.system("echo \'[LOG] -" + log + "\' >> log.txt")

while True:
        #connection done, waiting for commands
        try:
                data = connection.recv(1)               #read one char
        except:
                os.system('echo \'[ERROR] connection closed by user \' >> log.txt')
                break
        messagedata+=data
        if data != '\n':                # if end of command
                pass
        else:                           # parse command and write to sdtout
                messagedata = messagedata[:-1]          # cut new line
                if (messagedata == 'Exit'):
                        os.system('echo \'client disconnected normally \' >> log.txt')
                        break
                print messagedata               # write for stdout for atmega
                sys.stdout.flush()
                try:                    # sending acknowledge
                        connection.sendall(messagedata + 'back\n')
                        messagedata = ""
                except:
                        os.system('echo \'[ERROR]  sending feedback for user \' >> log.txt')

os.system('echo \'<==========- End of connection -==========>\' >> log.txt')

connection.close()
sock.shutdown(1)
sock.close()
