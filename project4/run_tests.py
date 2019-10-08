import glob
import os
import subprocess

path_public = os.path.join("public*.c")
public_tests = glob.glob(path_public)

link_file_names = ["machine.c"]
complier_name = "gcc"
run_files = []

link_file_name = " ".join(link_file_names)

run_tests = 0
save_logs = 1
run_cmd = 0


for public_file in public_tests:
    # get test name test it to output
    public_file_output_name = os.path.splitext(public_file)[0]+".x"
    run_files.append(public_file_output_name)

    cmd = [complier_name, public_file,
           link_file_name, "-o", public_file_output_name]
    cmd = " ".join(cmd)

    print(cmd)
    if run_cmd:
        gen_res = subprocess.run(cmd, stdout=subprocess.PIPE)
        if save_logs:
            with open("gen_log.log", "a") as file:
                file.write("Ran: " + cmd + "\n")
                file.write(gen_res.stdout.decode('utf-8'))

if run_cmd and run_tests:
    for run_file in run_files:
        run_res = subprocess.run(run_file, stdout=subprocess.PIPE)
        if save_logs:
            with open("run_log.log", "a") as file:
                file.write("Ran: " + run_file + "\n")
                file.write(run_res.stdout.decode('utf-8'))
