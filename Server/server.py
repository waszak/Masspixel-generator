'''
Created on 25-05-2013

@author: Waszak
'''
import sys
sys.path.append('../tools')#add tools to pythonpath
import socket
import select
from threading import Thread
import logging.config
import threading;
import time
import errno
from tools.CompressStrings import CompressStrings
import xml.etree.ElementTree as ET
import base64
import os

HOST, PORT = "localhost", 10069
NUMBER_TASKS_PER_CLIENT = 10 # arbitrary choosen number

logging.config.fileConfig("logging.conf")
logger = logging.getLogger('ConsoleLogger')

def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc: # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else: raise


#range with step 
def drange(start, stop, step):
    r = start
    while r < stop:
        yield r
        r += step

class TCPServer:
    def __init__(self, tasks, number_of_tasks_per_client):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)#
        self.clientNumber = 0
        self.chunk_size = 1024
        self.clientThreads = []
        self.running = False
        self.tasks = tasks
        self.number_of_tasks_per_client = number_of_tasks_per_client
        
    def bind(self, server_address, server_port):
        self.sock.bind((server_address, server_port))
    
    def client(self, connection, client_address):
        self.clientThreads.append(connection)
        self.clientNumber += 1
        tasks = self.tasks.getFreeTasks(self.number_of_tasks_per_client)
        msg = self.tasks.tasksToString(tasks)
        try:
            connection.sendall(CompressStrings.compress(msg))
            connection.shutdown(socket.SHUT_WR)
            data = ET.fromstring(self.downloadData(connection))
            for result in data.findall('./RESULT'):
                _id = result.get('ID')
                out = open('img\\id_'+_id+'.png','wb+')
                out.write(base64.b64decode(result.findtext('').encode('ASCII')))
            connection.close()
            self.tasks.returnComplitedTasks(tasks)
            if len(self.tasks.completed_tasks) == self.tasks.numberoftasks:
                self.running = False
        except Exception as ex:
            self.tasks.returnFailedTasks(tasks)
            logger.exception(ex)
            connection.close()
        
    def serve_forever(self):
        self.sock.listen(5)
        self.running = True
        while self.running:
            logger.info('waiting for a connection')
            connection, client_address = self.sock.accept()
            self.client(connection, client_address)
    
    def shut_down(self):
        self.running = False
        
    def downloadData(self, connection):
        data =b''
        while 1:
            try:
                ready = select.select([connection], [], [], 0.01)
                if not ready[0]:
                    continue
                chunk = connection.recv(self.chunk_size)
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

class Scene:
    def __init__(self,f_input, scene_width, scene_height, time, time_delta):
        self._f_input = open(f_input, 'r')
        self.time = time
        self.time_delta = time_delta
        self.width = scene_width
        self.height = scene_height
    
    def getWidth(self):
        return self.width
    
    def getHeight(self):
        return self.height
    
    def getDuration(self):
        return self.time
    
    def getDeltaTime(self):
        return self.time_delta
    
    def readInput(self):
        self.scena = self._f_input.read()
    
    def getScene(self):
        return self.scena
    
    def closeInput(self):
        self._f_input.close()

class Tasks:
    ROOT_BEGIN = '<ROOT>'
    ROOT_END = '</ROOT>'
    WIDTH = 'WIDTH='
    HEIGHT= 'HEIGHT='
    TASKS_BEGIN = '<TASKS>'
    TASKS_END = '</TASKS>'
    TASK_BEGIN = '<TASK>'
    TASK_END = '</TASK>'
    SCENA_BEGIN = '<SCENA'# to add attributes
    SCENA_END = '</SCENA>'
    CDATA_BEGIN = '<![CDATA['
    CDATA_END = ']]>'
    
    def __init__(self, scene):
        self.scene = scene
        
    def generateTasks(self):
        _id = 1
        self.tasks={}
        self.completed_tasks={}
        for i in drange(0,self.scene.getDuration(),scene.getDeltaTime()):
            self.tasks[_id] =  '%.5f' %round(i,5)
            _id += 1
        self.numberoftasks= _id - 1
        print(self.tasks)
    
    def getFreeTasks(self, number_of_tasks):
        freeTasks={}
        count = 0
        for key in self.tasks:
            count += 1
            if count >= number_of_tasks: 
                break
            freeTasks[key] = self.tasks[key]
       
        for key in freeTasks:
            self.tasks.pop(key)
    
        return freeTasks
    
    def tasksToString(self, tasks):
        taskString = Tasks.ROOT_BEGIN+'\n'
        taskString += Tasks.TASKS_BEGIN+'\n'
        for key in tasks:
            taskString += Tasks.TASK_BEGIN+'\n'
            taskString += str(key) + ' '+ tasks[key]+'\n' 
            taskString += Tasks.TASK_END+'\n'
        taskString += Tasks.TASKS_END+'\n'
        taskString += Tasks.SCENA_BEGIN+' '
        taskString += Tasks.WIDTH +'\'' +str(self.scene.getWidth())+'\''  + ' ' 
        taskString += Tasks.HEIGHT+'\''+ str(self.scene.getHeight())+'\'' + '>\n'
        taskString += Tasks.CDATA_BEGIN+'\n'
        taskString += self.scene.getScene()
        taskString += '\n'+Tasks.CDATA_END +'\n'
        taskString += Tasks.SCENA_END+'\n'
        taskString += Tasks.ROOT_END+'\n'
        return taskString
            
    def returnFailedTasks(self, failed_tasks):
        for key in failed_tasks:
            self.tasks[key] = failed_tasks[key]
    
    def returnComplitedTasks(self, tasks):
        for key in tasks:
            self.completed_tasks[key] = tasks[key]
                
def parse_data(argv):
    if len(argv) != 6:
        raise Exception("Invalid number of arguments")
    width=int(sys.argv[1])
    height=int(sys.argv[2])
    f_input = sys.argv[3]
    time = float(sys.argv[4])
    time_delta = float(sys.argv[5])
    return Scene(f_input, width, height, time, time_delta)

if __name__ == '__main__':
    mkdir_p("img")
    os.system("rmdir /s /q img")
    mkdir_p("img")
    # && rmdir /s /q img && mkdir img")
    try:
        scene = parse_data(sys.argv)
    except Exception as ex:
        logger.exception(ex)
        sys.exit('Usage: %s width height scene_file time time_delta' % sys.argv[0])
    try:
        scene.readInput()
    except Exception as ex:
        logger.error(ex)
        sys.exit('Error with reading scena')
    scene.closeInput()
    
    tasks = Tasks(scene)
    tasks.generateTasks()
    
    try:
        server = TCPServer(tasks, NUMBER_TASKS_PER_CLIENT)
        server.bind(HOST, PORT)
        server_thread = threading.Thread(target=server.serve_forever)
    except socket.error as ex:
        logger.exception(ex)
        sys.exit(1)
    
    server_thread.start()
    server_thread.join(timeout=None)
    os.system('bin\\ffmpeg.exe -f image2 -framerate 25 -pattern_type sequence -i "img\\id_%d.png" -s 720x480 -y out.avi && bin\\ffplay.exe out.avi')
    
    
    