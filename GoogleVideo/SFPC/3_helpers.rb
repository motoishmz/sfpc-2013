require 'net/http'
require 'uri'
require 'open-uri'
require 'resolv-replace'
require 'timeout'
require 'pp'  
require 'kconv'

K_TIMEOUT = 15
K_Google_Sbi = 'http://www.google.com.br/searchbyimage/upload'
K_User_Agent = '"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.94 Safari/537.4"'
K_Field_Name = 'encoded_image'


# ----
def write_log(str)
  f = File::open(PATH_DL_LOGS, "a")
  f.puts str
  f.close
end


# ---
# @return String (image url)
# @params String (original image filePath)
def get_similar_image_uri(original)
  
  # upload_res: the response of uploading image
  # @type Net::HTTPFound
  upload_res = upload_image(original)

  # sbi_search_uri: parsing 302_moved html to get the sbi url
  # @type String
  sbi_search_uri = get_sbi_url(upload_res.body)
  
  if (sbi_search_uri == "")
    
    return "" 
  else
    
    search_result_html = get_search_result(sbi_search_uri)
    img_uris = get_image_uris(search_result_html, 1)
    
    # returns 0th uri
    image_uri = img_uris[0]
    return image_uri
  end
end


# ---
# @return void 
# @params String (similar image url)
# @params Integer (frame index)
def save_image(url, index)
  
  # ready filepath
  dest_file_name = "frame-" + format("%04d", index) + File.extname(url)
  dest_file_path = PATH_DL_RAWFILES_DIR + dest_file_name
  
  p "start downloading: " + url
  
  begin
    timeout(K_TIMEOUT) do
      open(dest_file_path, 'wb') do |output|
        open(url) do |data|
          output.write(data.read)
        end
      end
    end
    
    # write the dest url to our log 
    write_log(url)
    
  rescue TimeoutError => e
      p "timeout! saving " + PATH_SRC_NOTFOUND_IMG
    
      open(dest_file_path, 'wb') do |output|
        open(PATH_SRC_NOTFOUND_IMG) do |data|
          output.write(data.read)
        end
      end
    
    # write the dest url to our log 
    write_log(LOG_NOT_FOUND)
    
  rescue => e
      p "unknown error... saving " + PATH_SRC_NOTFOUND_IMG
      pp "error reason:"
      pp e
      open(dest_file_path, 'wb') do |output|
        open(PATH_SRC_NOTFOUND_IMG) do |data|
          output.write(data.read)
        end
      end
    
    # write the dest url to our log 
    write_log(LOG_NOT_FOUND)
    
  end

  p "saved as: " + dest_file_name
end


# ---
# google does not allow the image search from script
# the response will be "302 moved" including correct uri
def upload_image(filename)

  # Create URI::HTTP
  uri = URI.parse(K_Google_Sbi)

  response = Net::HTTP.start(uri.host, uri.port){|http|

      # -----
      # request instance
      request = Net::HTTP::Post.new(uri.path)
      request["user-agent"] = K_User_Agent
      request["content-type"] = "multipart/form-data; boundary=myboundary"
    
      # -----
      # request body
      # (see also multipart/form-data spec)
      body = ""
      body.concat("--myboundary\r\n")
      body.concat("content-disposition: form-data; name=\"#{K_Field_Name}\"; filename=\"#{filename}\"\r\n")
      body.concat("\r\n")
      File::open(filename){|f| body.concat(f.read + "\r\n") }
    
      body.concat("--myboundary--\r\n")
      request.body = body
    
      # send request!
      http.request(request)
  }
  
  return response
end


# ---
# parsing html_302, and returns correct uri
def get_sbi_url(html_302)
  if /HREF="(.+?)"/ =~ html_302
    return $1
  else
    return PATH_SRC_NOTFOUND_IMG
  end
end


# ---
# get search result
# !!!:NOTE
# requests using Net.HTTP or Mechanize are denied!
# so let's use curl 
def get_search_result(sbi_url)
  return `curl -L -A #{K_User_Agent} #{sbi_url}`  
end



def get_image_uris(search_result_html, num_max_images = 1)
  

  results = []
  uri_pattern = Regexp.new(/imgurl=(http.+?)(&|%3F)/)
  
  # results.push(  )
  search_result_html.toutf8.scan(uri_pattern).each do |m|
    results << m[0]
  end

  return results.slice(0, num_max_images)
end
