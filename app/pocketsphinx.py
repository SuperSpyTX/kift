from ctypes import CDLL, create_string_buffer, byref, POINTER, cast, c_char_p, c_void_p, c_size_t, c_int, c_short
import struct

class PocketSphinx():
    def __init__(self, dylib_path, model_basepath):
        self.dylib_path = dylib_path
        self.model_basepath = model_basepath

    def is_loaded(self):
        return self.pocket != None

    def init(self):
        self.lib = CDLL(self.dylib_path)
        init = self.lib.init_sphinx
        init.restype = c_void_p
        buffer = create_string_buffer(self.model_basepath)
        self.pocket = init(buffer)
        return self.pocket != None

    def process(self, buff):
        if self.is_loaded() is False:
            return None
        proc = self.lib.process_data
        proc.restype = c_char_p
        proc.argtypes = [c_void_p, POINTER(c_short), c_size_t, c_int]
        proc(self.pocket, cast(0, POINTER(c_short)), 0, 0)
        buf = bytearray(1024)
        while buff.readinto(buf):
            count = int(len(buf) / 2)
            integers_t = c_short * count
            integers = struct.unpack('h'*count, buf)
            integers2 = integers_t(*integers)
            res = proc(self.pocket, cast(integers2, POINTER(c_short)), count, 1)
        res = proc(self.pocket, cast(0, POINTER(c_short)), 0, 2)
        print(res)
        return res.decode("UTF-8")

#pocket = PocketSphinx("wrapper/sphinx-wrapper.dylib", "wrapper/model")
#print(pocket.init())


