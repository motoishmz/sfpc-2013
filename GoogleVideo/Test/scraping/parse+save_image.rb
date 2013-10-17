require "helpers"
require 'fileutils'
require "open-uri"
require 'resolv-replace'
require 'timeout'

BASE_DIR = "../@assets/frames/"

def get_similar_image_url(original)
  
  # upload_res: the response of uploading image
  # @type Net::HTTPFound
  upload_res = upload_image(original)

  # sbi_search_uri: the parse result to get the sbi url
  # @type String
  sbi_search_uri = get_sbi_url(upload_res.body)


  if (sbi_search_uri == "")
    
    return "" 
    
  else
    
    search_result_html = get_search_result(sbi_search_uri)
    img_uris = get_image_uris(search_result_html, 1)
    
    image_url = img_uris[0]
    return image_url
    
  end
end

def save_image(url, index)
  
  notfound_image = BASE_DIR + "notfound.jpg"
  
  # ready filepath
  dirName = "./downloads/"
  fileName = "frame-" + format("%04d", index) + File.extname(url)
  filePath = dirName + fileName
  
  # create folder if not exist
  FileUtils.mkdir_p(dirName) unless FileTest.exist?(dirName)

  # write image adata
  
  p "start saving: " + File.basename(url)
  
  
  begin
    open(filePath, 'wb') do |output|
      open(url) do |data|
        output.write(data.read)
      end
    end
  rescue => e
      
      p "timeout! saving " + notfound_image
      
      open(filePath, 'wb') do |output|
        open(notfound_image) do |data|
          output.write(data.read)
        end
      end
  end

  p "saved as: " + fileName
end



frames = Dir::entries(BASE_DIR)

frames.each_with_index{|frame, i|
  
  file_path = BASE_DIR+frame
  
  next if File.ftype(file_path) != "file"
  
  cur_index = i - 2  # -2 => '.', '..'
  
  p "----"
  p cur_index.to_s + "/" + (frames.size-2).to_s  # -2 => '.', '..'
  p "start processing: " + file_path
  
  image_url = get_similar_image_url(file_path)
  save_image(image_url, cur_index)
}
