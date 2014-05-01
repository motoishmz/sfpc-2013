require "../conf.rb"
require 'pp'


# frame_dir_list = []
# image_hash = {}
# 
# 
# # -------------
# # original
# path = PATH_BASE_ASSETS+"frames_thumbs/"
# original_key = 'original'
# image_hash[original_key] = []
# frame_dir_list.push(original_key)
# 
# original_dir = Dir::entries(path)
# original_dir.each_with_index{|file, i|
#   
#   next if File.basename(file) =~ /^\./
# 
#   image_hash[original_key].push(path+file)
# }
# 
# 
# # -------------
# # pp image_hash
# 
# 
# # -------------
# # downloaded
# downloads_dir = Dir::entries(PATH_BASE_DOWNLOADS)
# downloads_dir.each_with_index{|dirName, i|
#   
#   next if File.basename(dirName) =~ /^\./
#   
#   image_hash[dirName] = []
#   frame_dir_list.push(dirName)
#   frame_path = PATH_BASE_DOWNLOADS + dirName + "/thumbs/"
#   
#   frames = Dir::entries(frame_path)
#   frames.each_with_index{|file, i|
#     
#     next if File.basename(file) =~ /^\./
#     image_hash[dirName].push(frame_path+file)
#     
#   }
# }



# pp frame_dir_list
# 
num_frames = 180
image_size = "50"

num_frames.times{ |i|

  index = sprintf("%04d", i+1)
  p "<img src=\"../../Assets/frames_thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-10-20/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-10-21/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-10-22/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-10-24/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-10-25/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-10-28/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-10-29/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-10-30/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-10-31/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-01/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-02/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-04/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-05/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-06/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-07/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-08/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-09/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-10/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-11/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-12/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-13/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-14/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-15/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-16/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-17/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-18/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p "<img src=\"../../Downloads/2013-11-19/thumbs/frame-#{index}.png\" width=\"#{image_size}\">"
  p
}
 
