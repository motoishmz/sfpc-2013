
# our config file
require '../conf.rb'

# gems
require 'rubygems'
require 'RMagick'

# see also
# http://gihyo.jp/dev/serial/01/ruby/0026
# http://ntt-rails.seesaa.net/article/71250230.html

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
  
    img.border(border_h, border_v, 'black')
  
  }.write(dest_path)
  
  p 'saved as: ' + dest_path
end


# ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
# our main code

frames = Dir::entries(PATH_DL_RAWFILES_DIR)

frames.each_with_index{|frame, i|
  
  src_file_path = PATH_DL_RAWFILES_DIR+frame
  framed_file_path = PATH_DL_FRAMED_DIR+frame
  
  next if File.ftype(src_file_path) != "file"
  next if File.basename(src_file_path) =~ /^\./
  
  begin
    create_frame(src_file_path, FINALIZE_WIDTH, FINALIZE_HEIGHT, framed_file_path);
  rescue
    create_frame(PATH_SRC_NOTFOUND_IMG, FINALIZE_WIDTH, FINALIZE_HEIGHT, framed_file_path);
  end
}


