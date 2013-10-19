
# our config file
require '../conf.rb' 
require 'helpers.rb'

# gems
require 'fileutils'
require 'open-uri'
require 'resolv-replace'
require 'timeout'


# ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
# our main code

frames = Dir::entries(PATH_SRC_RESIZE_DIR)

num_skip = 0;

frames.each_with_index{|frame, i|
  
  file_path = PATH_SRC_RESIZE_DIR+frame
  
  b_should_skip = ((File.ftype(file_path) != "file") || (File.basename(file_path) == ".DS_Store"))
  
  if b_should_skip
    num_skip+=1
    next
  end
  
  cur_index = i - num_skip
  
  p ''
  p '-----'
  p "start processing: " + (cur_index+1).to_s + "/" + (frames.size-num_skip).to_s + ", "+ file_path
  p 'src: ' + file_path
  image_url = get_similar_image_uri(file_path)
  save_image(image_url, cur_index+1)
}
