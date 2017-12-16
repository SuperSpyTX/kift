from ctypes import CDLL, POINTER, cast, c_char_p, c_void_p, c_size_t, c_short, c_int
import struct

class _PocketSphinxWrapperImpl():
    def __init__(self, libpath):
        self.lib = CDLL(libpath)
        self._init_sphinx = self.lib.init_sphinx
        self._init_sphinx.restype = c_void_p
        self._init_sphinx.argtypes = [POINTER(c_char_p), c_int]
        self._process_data = self.lib.process_voice_hypothesis
        self._process_data.restype = c_char_p
        self._process_data.argtypes = [c_void_p, POINTER(c_short), c_size_t]

        # Pocketsphinx API calls (not usually called directly)
        self._ps_free = self.lib.ps_free
        self._ps_free.argtypes = [c_void_p]

    def free(self, psinst):
        self._ps_free(psinst)

    def init_sphinx(self, args):
        args += [0] # Add null terminator for string array.
        size = len(args) - 1
        conv = [arg.encode('UTF-8') for arg in args if isinstance(arg, str)]
        strptr = (c_char_p * size)(*conv)
        return self._init_sphinx(strptr, size)

    def process_voice_data(self, psinst, intarr, size):
        integerptr_t = c_short * size
        ptr = integerptr_t(*intarr)
        return self._process_data(psinst, cast(ptr, POINTER(c_short)), size)

class _PocketSphinxInstance():
    def __init__(self, psobject):
        self._impl = _PocketSphinxWrapperImpl(psobject.libpath)
        self._pocket = self._impl.init_sphinx(psobject.generate_args())

    def is_loaded(self):
        return self._pocket != None

    def unload(self):
        if self.is_loaded() is False:
            return
        self._impl.free(self._pocket)

    def __del__(self):
        self.unload()

    def process(self, buff):
        if self.is_loaded() is False:
            return None
        size = int(len(buff) / 2)
        big_integer_array = struct.unpack('h' * size, buff)
        res = self._impl.process_voice_data(self._pocket, big_integer_array, size)
        if res is None:
            return ""
        return res.decode("UTF-8").lower()

class PocketSphinx():
    def __init__(self, libpath, modelpath, lmfile=None, dictionary=None):
        self.libpath = libpath
        self.debug = False
        self.language = 'en-us'
        self.modeldir = '{0}/{1}/{1}'.format(modelpath, self.language)
        if lmfile is None:
            self.lmfile = '{0}.lm.bin'.format(self.modeldir)
        else:
            self.lmfile = lmfile
        if dictionary is None:
            self.dict = '{0}/{1}/cmudict-{1}.dict'.format(modelpath, self.language)
        else:
            self.dict = dictionary

    def generate_args(self):
        args = ["-hmm", self.modeldir, "-lm", self.lmfile, "-dict", self.dict]
        if self.debug is False:
            args += ["-logfn", "/dev/null"]
        return args

    def initialize(self):
        return _PocketSphinxInstance(self)

    def __enter__(self):
        return self.initialize()

    def __exit__(self, exceptiontype, exceptionvalue, trace):
        pass
