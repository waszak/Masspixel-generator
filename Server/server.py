'''
Created on 25-05-2013

@author: Waszak
'''
import sys
sys.path.append('../tools')#add tools to pythonpath
import socket
from threading import Thread
import logging.config
import threading;
from tools.CompressStrings import CompressStrings


HOST, PORT = "localhost", 10000

logging.config.fileConfig("logging.conf")
logger = logging.getLogger('ServerConsoleLogger')


class Send:
    def __init__(self, msg):
        pass
         
    def mysend(self, msg):
        totalsent = 0
        while totalsent < msg.length:
            sent = self.sock.send(msg[totalsent:])
            if sent == 0:
                raise RuntimeError("socket connection broken")
            totalsent = totalsent + sent
    
    def myreceive(self):
        msg = ''
        '''while len(msg) < MSGLEN:
            chunk = self.sock.recv(MSGLEN-len(msg))
            if chunk == '':
                raise RuntimeError("socket connection broken")
            msg = msg + chunk
        return msg'''
    
class TCPServer:
    def __init__(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.clientNumber = 0
        self.clientThreads = []
        self.running = False
        #self.__lock__ = threading.Lock()
        
    def bind(self, server_address, server_port):
        self.sock.bind((server_address, server_port))
    
    def client(self, connection, client_address):
        self.clientThreads.append(connection)
        self.clientNumber += 1
        ex=[]
        for i in range(0,1024*1024):
            ex.append('a')
        connection.send(CompressStrings.compress(ex))
        print(client_address)
        
    def serve_forever(self):
        self.sock.listen(1)
        #self.__lock__.acquire()
        self.running = True
        while self.running:
            #self.__lock__.release()
            logger.info('waiting for a connection')
            connection, client_address = self.sock.accept()
            self.client(connection, client_address)
            #self.__lock__.acquire()
    
    def shut_down(self):
        #self.__lock__.acquire()
        self.running = False
        #self.__lock__.release()

if __name__ == '__main__':
    #runserver()
    try:
        server = TCPServer()
        server.bind(HOST, PORT)
        server_thread = threading.Thread(target=server.serve_forever)
    except socket.error as ex:
        logger.exception(ex)
        sys.exit(1)
    
    server_thread.start()
    server.shut_down()
    server_thread.join(timeout=None)
    print("Hello Word")
