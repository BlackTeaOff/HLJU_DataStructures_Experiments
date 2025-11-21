from flask import Flask, render_template
import ctypes # 调用动态链接库(可以是C编译出的DLL)

app = Flask(__name__)

class Place(ctypes.Structure):
        _fields_ = [("name", ctypes.c_char * 100),
                    ("intro", ctypes.c_char * 100)]

dll_path = "D:\\Qt_Project\\Data_Structures\\EXP_8\\HLJU_Guide.dll"

guide_dll = ctypes.CDLL(dll_path) # 加载dll

guide_dll.init.argtypes = [] # 设置每个函数的类型和返回类型
guide_dll.init.restype = None

guide_dll.fromGatePath.argtypes = [ctypes.c_int] # 参数dest
guide_dll.fromGatePath.restype = ctypes.c_char_p # 返回结果json字符串(char类型指针)

guide_dll.fromPlacePath.argtypes = [ctypes.c_int, ctypes.c_int]
guide_dll.fromPlacePath.restype = ctypes.c_char_p

guide_dll.getPlaces.argtypes = []
guide_dll.getPlaces.restype = ctypes.POINTER(Place)

guide_dll.init()
print("DLL加载成功")

places_ptr = guide_dll.getPlaces()
PLACES_DATA = []
for i in range(10):
    PLACES_DATA.append({
        "id": i,
        "name": places_ptr[i].name.decode('utf-8'),
        "intro": places_ptr[i].intro.decode('utf-8')
    })

@app.route('/') # /页面(主页)
def index():
    return render_template('index.html')

@app.route('/query-from-gate')
def query_from_gate_page():
    return render_template('fromgate.html', places=PLACES_DATA)

@app.route('/path/from_gate/<int:dest>') # 用于给页面返回数据
def path_from_gate_api(dest):
    result_c = guide_dll.fromGatePath(dest)
    result = result_c.decode('utf-8') # 转为python类型的字符串
    return result

@app.route('/query-from-place')
def query_from_place_page():
     return render_template('fromplace.html', places=PLACES_DATA)

@app.route('/path/from_place/<int:src>/to/<int:dest>')
def path_from_place_api(src, dest):
    result_c = guide_dll.fromPlacePath(src, dest)
    result = result_c.decode('utf-8')
    # print(result)
    return result

@app.route('/placeinfo')
def place_info():
     return render_template('place_info.html')

if __name__ == '__main__':
    app.run()