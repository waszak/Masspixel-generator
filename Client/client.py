'''
Created on 20-05-2013

@author: Waszak
'''

import random
import errno
import logging
import logging.config
import select
import socket
import base64
import sys
import time
import os
import xml.etree.ElementTree as ET
import subprocess
sys.path.append('../tools')#add tools to pythonpath
from tools.CompressStrings import CompressStrings, invalidCheckSumException

HOST, PORT = "localhost", 10069

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
    
    def reconnect(self):
        self.connection = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connect()
        
    def sendResult(self,res):
        self.connection.sendall(CompressStrings.compress(res))
    
    def downloadData(self):
        data =b''
        while 1:
            try:
                ready = select.select([self.connection], [], [], 0.01)
                if not ready[0]:
                    continue
                chunk = self.connection.recv(self.chunk_size)
                if not chunk: break
                #logger.info('socket get chunk')
                data += chunk
            except socket.error as e:
                if e.args[0] == errno.EWOULDBLOCK: 
                    time.sleep(0.01)           # short delay, no tight loops
                else:
                    logger.error(e)
                    break
        return CompressStrings.decompress(data) 

"""
class ParseScene:
    ROOT_BEGIN = '<ROOT>'
    ROOT_END = '</ROOT>'
    WIDTH = 'WIDTH='
    HEIGHT= 'HEIGHT='
    TASKS_BEGIN = '<TASKS>'
    TASKS_END = '</TASKS>'
    TASK_BEGIN = '<TASK>'
    TASK_END = '</TASK>'
    SCENA_BEGIN = '<SCENA>'
    SCENA_END = '</SCENA>'
"""
    
class ResultXMLTag:
    ROOT_BEGIN = '<ROOT>'
    ROOT_END = '</ROOT>'
    RESULT_BEGIN='<RESULT'
    RESULT_END='</RESULT>'
    CDATA_BEGIN = '<![CDATA['
    CDATA_END = ']]>'
    
"""def com(job_query, result_query):
    while True:
        result_query = { n: n for n in job_query}
        print (result_query)
"""    
class Job:
    def __init__(self,data):
        self.data = data
        
    def start(self):
        #TODO
        pass
    def result(self):
        self.output = 'finished'
        return True
    
    def saveScena(self, path):
        root = ET.fromstring(self.data)
        scena = root.findtext('SCENA').strip()
        scena_file = open(path, 'w+')
        scena_file.write(scena)
        self.scena_path = scena_file.name
        scena_file.close()
    
    def readTasks(self):
        self.tasks = {}
        root = ET.fromstring(self.data)
        p = root.find('./SCENA')
        self.width= p.get('WIDTH')
        self.height = p.get('HEIGHT')
        for task in root.findall('./TASKS/TASK'):
            x = task.findtext('.').strip().split(' ')
            self.tasks[x[0]]= x[1]
    
    def doTasks(self, path):
        os.chdir("bin")
        for key in self.tasks:
            #os.system('MasspixelRenderer.exe id_'+key+'.png ' +"../"+path+' ' +self.width+ ' '+ self.height+ ' '+ self.tasks[key])
            subprocess.call(('MasspixelRenderer.exe', 'id_'+key+'.png ', "../"+path+' ' ,self.width+ ' ', self.height+ ' ', self.tasks[key]))
        os.chdir("../")
    def getResult(self):
        stringResult = ResultXMLTag.ROOT_BEGIN + '\n'
        for key in self.tasks:
            f = open('bin\\id_'+key+'.png','rb+')
            stringResult += ResultXMLTag.RESULT_BEGIN+' '+'ID=\''+key+'\'>\n'
            stringResult += ResultXMLTag.CDATA_BEGIN+'\n'
            stringResult +=  base64.b64encode(f.read()).decode('ascii')
            stringResult += '\n'+ ResultXMLTag.CDATA_END+'\n'
            stringResult += ResultXMLTag.RESULT_END+'\n'
        stringResult += ResultXMLTag.ROOT_END
        return stringResult
    
if __name__ == "__main__":
    client = Client(HOST, PORT)
    try:
        client.connect() 
        while True:
            data = client.downloadData()
            job = Job(data)
            job.saveScena('frag.frag')
            job.readTasks()
            job.doTasks('frag.frag')
            client.sendResult(job.getResult())
            client.reconnect()
    except socket.error as ex:
        logger.exception(ex)
        sys.exit(1)
    except Exception as ex:
        logger.exception(ex)
        sys.exit(1)
        