
# our config file
require '../conf.rb' 


# ---
# execute: slice all frames
# ffmpeg -i (srcFileName) -f image2 -vcodec (format) "path_to_save_file"

format = SRC_FRAME_EXTENTION # jpeg, png...
source = SRC_MOVIE_FILE
dest = "#{PATH_SRC_FRAMES_DIR}frame-%04d.#{SRC_FRAME_EXTENTION}"
command = "/usr/local/bin/ffmpeg -i '#{source}' -f image2 -vcodec #{format} '#{dest}'"

`#{command}` # fire


# ---
# resizing all frames to 640:360

frames = Dir::entries(PATH_SRC_FRAMES_DIR)

frames.each_with_index{|frame, i|
  
  file_path = PATH_SRC_FRAMES_DIR + frame
  dest_path = PATH_SRC_RESIZE_DIR + frame
  
  next if File.ftype(file_path) != "file"
  next if File.basename(file_path) == ".DS_Store"
  
  command = "/usr/local/bin/ffmpeg -i #{file_path} -vf scale=#{FINALIZE_WIDTH}:#{FINALIZE_HEIGHT} #{dest_path}"
  
  `#{command}` # fire
}
