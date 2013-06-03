'''
Created on 20-05-2013

@author: Waszak
'''
from tools.CompressStrings import CompressStrings, invalidCheckSumException
import logging
import socket
import sys
sys.path.append('../tools')#add tools to pythonpath

HOST, PORT = "localhost", 10000

logging.config.fileConfig("logging.conf")
logger = logging.getLogger('ClientConsoleLogger')

class Client:
    def __init__(self,server_address, server_port):
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_address = (server_address, server_port)
        
    def connect(self):
        self.connection.connect(self.server_address)
    
    def reconnct(self):
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connection.connect(self.server_address)
        
def com(job_query, result_query):
    while True:
        result_query = { n: n for n in job_query}
        print (result_query)
    
class Job:
    def __init__(self, input):
        self.input = input
    def start(self):
        pass
    def result(self):
        return 'finished'

if __name__ == "__main__":
    client = Client(HOST, PORT)
    try:
        client.connect()
    except socket.error as ex:
        logger.exception(ex)
        sys.exit(1)
    while 1:
        data = sock.recv(1024)
        if not data: break
        print (data)
        try:
            print( CompressStrings.decompress(data))
            print( len(CompressStrings.decompress(data)))
        except invalidCheckSumException as e:
            print(e)
        