"""
    Script that adds new C++ class to project
"""
import os

def get_line():
    number = 0
    try:
        path = os.getcwd() + "\scripts\data\line.txt"
        file = open(path, 'r')
        line = file.readline()
        number = line.split("=")[1]
        file.close()

        file = open(path, 'w')
        file.write(f"FILE={int(number) + 1}")
    except Exception:
        print("Failed to open file")

    return number

def insert(path, name):
    with open(path, 'r') as file:
        data = file.readlines()

    num = int(get_line())
    data[num] = f"\tsrc/{name}.cpp src/{name}.hpp\n"
    data[num + 1] = ")\n"
    data[num + 2] = f"\n{data[num + 2]}"
    
    with open(path, 'w') as file:
        file.writelines(data)

def main():
    class_name = input("Enter class name: \n")
    try:
        open(os.getcwd().removesuffix("\scripts") + f"\src\{class_name}.cpp", 'x')
        open(os.getcwd().removesuffix("\scripts") + f"\src\{class_name}.hpp", 'x')
        insert(os.getcwd() + "\CMakeLists.txt", class_name)
    except Exception:
        print("Failed to create new files")

if __name__ == "__main__":
    main()