
# our config file
require "./conf.rb" 
require './3_helpers.rb'

# gems
require 'FileUtils'

# ---
# create result dir
FileUtils::mkdir_p(PATH_BASE_DOWNLOADS + TODAY) unless FileTest.exists?(PATH_BASE_DOWNLOADS + TODAY)
FileUtils::mkdir_p(PATH_DL_RAWFILES_DIR) unless FileTest.exists?(PATH_DL_RAWFILES_DIR)
FileUtils::mkdir_p(PATH_DL_FRAMED_DIR) unless FileTest.exists?(PATH_DL_FRAMED_DIR)
FileUtils::mkdir_p(PATH_DL_THUMBS_DIR) unless FileTest.exists?(PATH_DL_THUMBS_DIR)

# logfile
f = File::open(PATH_DL_LOGS, "w")
f.puts TODAY
f.puts "--------------------------"
f.close

# ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
# our main code

frames = Dir::entries(PATH_SRC_RESIZE_DIR)

num_skip = 0;

frames.each_with_index{|frame, i|
  
  file_path = PATH_SRC_RESIZE_DIR+frame
  
  b_should_skip = ((File.ftype(file_path) != "file") || (File.basename(file_path) =~ /^\./))
  
  if b_should_skip
    num_skip+=1
    next
  end
  
  cur_index = i - num_skip
  
  # next if cur_index < 22
  
  p "====================================================================================="
  p "start processing: " + (cur_index+1).to_s + "/" + (frames.size-num_skip).to_s + ", "+ file_path
  p 'src: ' + file_path
  image_url = get_similar_image_uri(file_path)
  save_image(image_url, cur_index+1)
}
