import subprocess
import os
import shutil

path = os.path.dirname(os.path.realpath(__file__))
repo_root = os.path.join(path, "..")

# Copy the report.json from the build directory to json/progress.json
report_src = os.path.join(repo_root, "build", "G5SE7D", "report.json")
report_dst = os.path.join(path, "json", "progress.json")

os.makedirs(os.path.join(path, "json"), exist_ok=True)
shutil.copy2(report_src, report_dst)
print(f"Copied {report_src} -> {report_dst}")

commands = [
    "npm install",
    "npm run build"
]

for command in commands:
    print(command)
    proc = subprocess.run(command, shell=True, cwd=path)
    if proc.returncode != 0:
        raise RuntimeError(f"Command {command} failed with return code {proc.returncode}")
