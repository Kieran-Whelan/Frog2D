"""
    Script that adds new C++ class to project
"""
import os

data_path = os.getcwd() + "/scripts/data/line.txt"
cmake_path = os.getcwd() + "/CMakeLists.txt"

class EngineClass:
    def __init__(self, name, path):
        self.name = name
        self.path = path

def get_line():
    number = 0
    try:
        file = open(data_path, 'r')
        line = file.readline()
        number = line.split("=")[1]
        file.close()
    except Exception:
        print("Failed to open file")

    return int(number)

def inc_line(line):
    try:
        file = open(data_path, 'w')
        file.write(f"FILE={line + 1}")
        file.close()
    except Exception:
        print("Failed to increment line")

def insert(path, string, line):
    data = get_content(path)

    num = line
    data[num] = string

    write_content(path, data)

def get_content(path):
    with open(path, 'r') as file:
        return file.readlines()

def write_content(path, data):
    with open(path, 'w') as file:
        file.writelines(data)

def main():
    class_name = input("Enter class name: \n")
    path_name = "/" + input("Enter path name (if path is src/ leave blank): \n")
    engine_class = EngineClass(class_name, path_name)
    try:
        open(os.getcwd() + f"/src{engine_class.path}/{engine_class.name}.cpp", 'x')
        open(os.getcwd() + f"/src{engine_class.path}/{engine_class.name}.hpp", 'x')

        #brute force fix
        string = f"\n{get_content(cmake_path)[get_line() + 2]}"
        insert(cmake_path, f"\tsrc{engine_class.path}/{class_name}.cpp src{engine_class.path}/{class_name}.hpp\n", get_line())
        insert(cmake_path, ")\n", get_line() + 1)
        insert(cmake_path, string, get_line() + 2)

        inc_line(get_line())
    except Exception:
        print("Failed to create new files")

if __name__ == "__main__":
    main()