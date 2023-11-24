import os
import platform
import subprocess

path_del = "\\" if platform.system() == "Windows" else "/" 

COMPILER = "gcc"
BUILDDIR = "build"
LIB = "lib"
ENTRY = "main.c"
DEBUG = True

if not os.path.exists(BUILDDIR):
    os.makedirs(BUILDDIR)

def compile_source(source, output):
    try:
        subprocess.run([COMPILER, source, "-c", "-o", output], check=True)
        print(f"Compilé {source} avec succès.")
    except subprocess.CalledProcessError:
        print(f"Erreur: Compilation de {source} a échoué.")
        exit(1)

def link_objects(entry, objects, output):
    try:
        command = [COMPILER, entry] + (['-g'] if DEBUG else []) + objects + ["-o", output]
        subprocess.run(command, check=True)
        print("Liaison réussi.")
    except subprocess.CalledProcessError:
        print("Erreur: Liaison a échoué.")
        exit(1)

path_objs = []
for file in os.listdir(LIB):
    filename, ext = os.path.splitext(file)
    if ext == '.c':
        path_obj = f"{BUILDDIR}{path_del}{filename}.o"
        path_objs.append(path_obj)
        compile_source(f"{LIB}{path_del}{file}", path_obj)

link_objects(ENTRY, path_objs, "main")
