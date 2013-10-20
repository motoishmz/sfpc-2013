
# our config file
require '../conf.rb' 

# gems
require 'FileUtils'


# ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
# new movie!
# ffmpeg -r 30 -i assets/frames/frame-%4d.png -qscale 1 out.avi

frame_rate = FINALIZE_FRAME_RATE.to_s
input_files = PATH_MOVIE_FRAMES_DIR + 'frame-%04d.' + SRC_FRAME_EXTENTION
output_file = PATH_MOVIE_NEW

command = '/usr/local/bin/ffmpeg -r '+ frame_rate + ' -i ' + input_files + ' -qscale 1 ' + output_file

FileUtils.rm(output_file) if File.exist?(output_file)

`#{command}` # fire