"""
    Script that adds new shaders to project
"""
import os

shader_path = f"{os.getcwd()}/res/shaders/"
template_path = f"{os.getcwd()}/scripts/templates/"

def get_content(file):
    with open(file, 'r') as f:
        return f.readlines()

def main():
    shader_name = input("Enter shader name: \n")
    try:
        vertex_file = open(shader_path + f"{shader_name}_vertex.glsl", 'w')
        vertex_file.writelines(get_content(template_path + "vertex_template.glsl"))
        vertex_file.close()

        fragment_file = open(shader_path + f"{shader_name}_fragment.glsl", 'w')
        fragment_file.writelines(get_content(template_path + "fragment_template.glsl"))
        fragment_file.close()
    except Exception:
        print("An error occurred while creating shaders")

if __name__ == "__main__":
    main()