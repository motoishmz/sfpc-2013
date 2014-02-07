require 'open-uri'

dir_name = ARGV[0] || "sfpc.hackpad.com"
img_dir_name = "#{dir_name}/img"
Dir::mkdir(dir_name) unless FileTest::directory?(dir_name)
Dir::mkdir(img_dir_name) unless FileTest::directory?(img_dir_name)


# image:
#   ![](https://hackpad-attachments.s3.amazonaws.com/hackpad.com_PUoCY2js9sB_p.77239_1384196123283_undefined)
#   /\!\[\].*?(https:\/\/hackpad-attachments.s3.amazonaws.com\/.+)\)$/x
#   
# page link: 
#   (/pUrFgJQucxm)
#   /\(\/[a-zA-Z]{11}\)/
# 
# pad_id:
#   /abcdefghijk
#   /-([0-9a-zA-Z]{11})\.md$/
reg_img = /\!\[\].*?(https:\/\/hackpad-attachments.s3.amazonaws.com\/.+)\)/x
reg_link = /\(\/([a-zA-Z]{11})\)/
reg_id = /-([0-9a-zA-Z]{11})\.md$/
  
#----------------------------------------------------------------

def save_file(image_url, dest)
  
  p "::: [start downloads] #{image_url}"
  
  open(dest, 'wb') do |file|
    open(URI.escape(image_url)) do |data|
      file.write(data.read)
    end
  end
  
  p "::: [saved as       ] #{dest}"
end

#----------------------------------------------------------------


# file name array
pads = Dir::entries(dir_name)


# ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
pads.each_with_index{|pad, i|
  
  file_path = "#{dir_name}/#{pad}"
  
  next if File.ftype(file_path) != "file"
  next if File.basename(file_path) =~ /^\./
  
  p "======================="
  p "[#{i-2}]" + File.basename(file_path)
  
  str = ""
  img_index = 0;
  pad.match(reg_id)
  pad_id = $1
  
  f = open(file_path)
  while line = f.gets
    
    # ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
    # download all images
    if reg_img =~ line
      
      image_url = $1
      dest_filename = "#{pad_id}-#{img_index}.png"
      dest_path = "#{img_dir_name}/#{dest_filename}"
      
      save_file($1, dest_path)
      img_index = img_index+1;
      
      # replace
      line.gsub!(image_url, dest_path)
      p "::: [replaced: before] #{image_url}"
      p "::: [replaced: after ] #{dest_filename}"
      p "---"
    end
    
    
    # ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
    # create new link
    if reg_link =~ line
      
      href = $1
      new_href = ""
      
      pads.each{|filename|
        if filename.match(href)
          new_href = filename
          break;
        end
      }
      
      # replace
      p "---"
      p line
      line.gsub!("/"+href, new_href)
      p "replaced before: #{href}"
      p "replaced after : #{new_href}"
      
    end
    
    # store new line
    str << line
  
  end
  f.close
  
  
  f = open(file_path, "w")
  f.puts str
  f.close
}

