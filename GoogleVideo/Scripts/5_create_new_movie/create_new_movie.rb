

# our config file
require '../conf.rb' 

# gems
require 'rubygems'
require 'RMagick'
require 'FileUtils'
require 'pp'

# 1. 画像を合成
# 2. 各フレームからmovieつくる
# ffmpeg -r 30 -i assets/frames/frame-%4d.png -qscale 1 out.avi


FileUtils::mkdir_p(PATH_MOVIE_TODAY_DIR) unless FileTest.exists?(PATH_MOVIE_TODAY_DIR)
FileUtils::mkdir_p(PATH_MOVIE_FRAMES_DIR) unless FileTest.exists?(PATH_MOVIE_FRAMES_DIR)

# frames.each_with_index{|frame, i|
#   
#   file_path = BASE_DIR+frame
#   
#   next if File.ftype(file_path) != "file"
#   next if File.basename(file_path) == ".DS_Store"
#   
#   cur_index = i - 2  # -2 => '.', '..'
# }


original_files = Dir::entries(PATH_SRC_RESIZE_DIR)
similar_files = Dir::entries(PATH_DL_FRAMED_DIR)

original_files.delete(".")
original_files.delete("..")
original_files.delete(".DS_Store")

similar_files.delete(".")
similar_files.delete("..")
similar_files.delete(".DS_Store")


pp "original_files: " + original_files.size.to_s
pp "similar_files: " + similar_files.size.to_s



original_files.each_with_index{|frame, i|
  
  fileName = "frame-" + format("%04d", i+1)
  
  img_a = PATH_SRC_RESIZE_DIR + original_files[i]
  img_b = PATH_DL_FRAMED_DIR + similar_files[i]
  
  image1 = Magick::ImageList.new( img_a )
  image2 = Magick::ImageList.new( img_b )
  
  new_width = FINALIZE_WIDTH * 2
  new_height = FINALIZE_HEIGHT 
  
  dst = Magick::Image.new( new_width, new_height ){ self.background_color = "black" }
  dst.composite!( image1, 0, 0, Magick::OverCompositeOp )
  dst.composite!( image2, FINALIZE_WIDTH, 0, Magick::OverCompositeOp )
  
  dst.write( PATH_MOVIE_FRAMES_DIR + fileName + "." + SRC_FRAME_EXTENTION );  
  p fileName + " saved."
}
