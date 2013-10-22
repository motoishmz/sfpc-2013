
# our config file
require '../conf.rb' 

# ---
# get src movie framerate using ffmpeg
#   - http://mgng.aws.af.cm/456

#  get movie info
log_file_name = "movie_info.txt"
`/usr/local/bin/ffmpeg -i #{SRC_MOVIE_FILE} 2> #{log_file_name}`

# frame rate
f = open(log_file_name)
f.each {|line| p "original movie is [ " + $1.to_s + " ] fps" if line =~ /(\d+\.\d+|\d+)\s*fps/}
f.close


