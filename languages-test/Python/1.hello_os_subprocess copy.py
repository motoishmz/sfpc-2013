import os
import subprocess

# --- 
myname = os.getlogin()
print( "hello my name is " + myname )
# subprocess.check_call("say my name is " + myname, shell=True)


# --- 
location = os.path.abspath('.')
print( "current path is " + location )


# --- 

# list of files in sfpc-2013 dir
print( "--- list of files in sfpc-2013 dir ---" )
for i in os.listdir(location+"/../"):
	filename = os.path.join(location, i)
	print( filename )