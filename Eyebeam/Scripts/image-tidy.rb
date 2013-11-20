
require 'rubygems'
require 'RMagick'

def create_frame(src_path, w, h, dest_path)
  
  p 'start creating frame: ' + src_path
  image = Magick::Image.read(src_path).first
  
  image.change_geometry!("#{w}x#{h}>") { |cols, rows, img|
  
    cols, rows = [cols, rows].map { |i| (i / 2).round * 2 }
    img.resize_to_fit!(cols, rows)
  
    border_h = (w - cols) / 2
    border_v = (h - rows) / 2
    
    border_h += 1 if (border_h%2 == 1)
    border_v += 1 if (border_v%2 == 1)
    
    border_h += 1 if (border_h < 0)
    border_v += 1 if (border_v < 0)
    
    img.border(border_h, border_v, 'white')
  
  }.write(dest_path)
  
  p 'saved as: ' + dest_path
end



# ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
# our main code
FINALIZE_WIDTH = 1517.58
FINALIZE_HEIGHT = 1138.18

source_dir = "/Users/motoishmz/Documents/Project_Stack/!screenshots/"
frames = Dir::entries(source_dir)

frames.each_with_index{|frame, i|
  
  src_file_path = source_dir+frame
  dest_file_path = "../Resized/"+frame
  
  next if File.ftype(src_file_path) != "file"
  next if File.basename(src_file_path) =~ /^\./
  next if i < 122
  
  p '----'
  p '[' + i.to_s + ']'
  create_frame(src_file_path, FINALIZE_WIDTH, FINALIZE_HEIGHT, dest_file_path);
}
