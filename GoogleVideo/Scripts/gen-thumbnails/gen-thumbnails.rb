

def gen_thumbnails( date )
	
	source = "../../Downloads/"+ date +"/framed/"
	dest   = "../../Downloads/"+ date +"/thumbs/"

	frames = Dir::entries(source)

	frames.each_with_index{|frame, i|
	  
	  file_path = source + frame
	  dest_path = dest + frame

	  next if File.ftype(file_path) != "file"
	  next if File.basename(file_path) =~ /^\./
	  
	  command = "/usr/local/bin/ffmpeg -i #{file_path} -vf scale=#{THUMB_MAX_WIDTH}:#{THUMB_MAX_HEIGHT} #{dest_path}"
	  
	  p "start resizeing: " + file_path
	  `#{command}` # fire
	  p "finished. saved ad: " + dest_path
	}

end



# ･゜･*:.｡..:*･'｡. .｡.:*･゜･*
# our main code
sources = [
"2013-10-20",
"2013-10-21",
"2013-10-22",
"2013-10-24",
"2013-10-25",
"2013-10-28",
"2013-10-29",
"2013-10-30",
"2013-10-31",
"2013-11-1",
"2013-11-10",
"2013-11-11",
"2013-11-12",
"2013-11-13",
"2013-11-14",
"2013-11-15",
"2013-11-16",
"2013-11-17",
"2013-11-2",
"2013-11-4",
"2013-11-5",
"2013-11-6",
"2013-11-7",
"2013-11-8",
"2013-11-9"
]


sources.each_with_index{ |date, index|

	gen_thumbnails(date)

}






