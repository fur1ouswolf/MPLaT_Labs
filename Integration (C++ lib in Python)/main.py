import ctypes
import numpy as np
import matplotlib.pyplot as plt
import glob
import os

def load_function(lib_name, func_name):
    lib = ctypes.CDLL(lib_name)
    if not hasattr(lib, func_name):
        print(f"Function {func_name} not found in {lib_name}")
        return
    func = lib.__getattr__(func_name)
    func.argtypes = (ctypes.POINTER(ctypes.c_double), ctypes.c_size_t, ctypes.POINTER(ctypes.c_double))
    return func

def calc_f(func, x):
    n = len(x)
    x_arr = (ctypes.c_double * n)(*x)
    y_arr = (ctypes.c_double * n)()
    func(x_arr, n, y_arr)
    return np.array(y_arr)

def main():
    lib_files = glob.glob('*.so')
    print("Libraries:")
    for i, lib in enumerate(lib_files):
        print(f"{i+1}. {lib}")
    choice = int(input("Select library: ")) - 1
    selected_lib = lib_files[choice]
    func_name = "calculate"

    try:
        func = load_function(selected_lib, func_name)
        x_min = -20.0
        x_max = 20.0
        num_points = 10000
        x = np.linspace(x_min, x_max, num_points)
        y = calc_f(func, x)

        plt.plot(x, y)
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title('y = f(x)')
        plt.show()

    except Exception:
        print("ALARM!!!")

if __name__ == "__main__":
    main()


