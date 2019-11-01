import subprocess

global program

def before_all(context):
    global program
    print("Starting the Mahjong game...")
    program = subprocess.Popen(['build/src/game'], 
                            stdout=subprocess.PIPE,
                            universal_newlines=True)
    output = program.stdout.readline()
    if not output.startswith("httpd running on port 8889"):
        print("Failed to start the game.\n Got response '" + output +"'")
        context.aborted = True

def after_all(context):
    program.kill()

