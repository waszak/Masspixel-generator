'''
Created on 20-05-2013

@author: Waszak
'''


import errno
import logging
import logging.config
import select
import socket
import sys
import time
sys.path.append('../tools')#add tools to pythonpath
from tools.CompressStrings import CompressStrings, invalidCheckSumException

HOST, PORT = "localhost", 10002

logging.config.fileConfig("logging.conf")
logger = logging.getLogger('ConsoleLogger')

class Client:
    def __init__(self,server_address, server_port):
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_address = (server_address, server_port)
        self.chunk_size = 1024
        
    def connect(self):
        self.connection.connect(self.server_address)
        self.connection.setblocking(False)
        self.connection.settimeout(0.1)
    
    def reconnct(self):
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connection.connect()
        
    def getTasks(self):
        pass
    '''TODO, refactor'''
    def downloadData(self):
        data =b''
        while 1:
            try:
                ready = select.select([self.connection], [], [], 0.01)
                if not ready[0]:
                    continue
                logger.info('socket get sht')
                chunk = self.connection.recv(self.chunk_size)
                if not chunk: break
                logger.info('socket get chunk')
                data += chunk
            except socket.error as e:
                if e.args[0] == errno.EWOULDBLOCK: 
                    time.sleep(0.01)           # short delay, no tight loops
                else:
                    logger.error(e)
                    break
        #print( CompressStrings.decompress(data))
        print( len(CompressStrings.decompress(data)))
        
def com(job_query, result_query):
    while True:
        result_query = { n: n for n in job_query}
        print (result_query)
    
class Job:
    def __init__(self, input):
        self.input = input
    def start(self):
        #TODO
        pass
    def result(self):
        self.output = 'finished'
        return True

if __name__ == "__main__":
    client = Client(HOST, PORT)
    try:
        client.connect()
        client.downloadData()
    except socket.error as ex:
        logger.exception(ex)
        sys.exit(1)
        