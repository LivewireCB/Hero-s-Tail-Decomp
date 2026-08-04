import subprocess
import os

path = os.path.dirname(os.path.realpath(__file__))

commands = [
    "npm install",
    "npm run build"
]

for command in commands:
    print(command)
    proc = subprocess.run(command, shell=True, cwd=path)
    if proc.returncode != 0:
        raise RuntimeError(f"Command {command} failed with return code {proc.returncode}")
