import io
import gzip

class invalidCheckSumException(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)

class gzipCheckSum(gzip.GzipFile):
    def _read_eof(self):#function throws exception when CRC is invalid or length
        try:
            super(gzipCheckSum,self)._read_eof()
        except IOError as e:
            raise invalidCheckSumException(str(e))
    
class CompressStrings:
    TAG='<_string_>'
    @staticmethod
    def compress( msg):
        out = io.BytesIO()
        f = gzip.GzipFile(fileobj=out, mode='w')
        f.write(bytes(msg, 'UTF-8'))
        f.close()
        result = out.getvalue()
        out.close()
        return result
    @staticmethod
    def decompress(compressed_data):
        _in = io.BytesIO(compressed_data)
        f = gzipCheckSum(fileobj=_in, mode='rb')
        try:
            result = f.read().decode()
        except invalidCheckSumException as e:
            raise e
        f.close()
        return result
