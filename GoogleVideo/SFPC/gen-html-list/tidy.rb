
filename = ARGV[0] || "test.html"

#
# IO#getsを使う例
#
p filename
str = ""
f = open(filename)
while line = f.gets
  
  line.gsub!(/^"/, '')
  line.gsub!(/"$/, '')
  line.gsub!('\"', '"')
  str << line
  
end
f.close


f = open(filename, "w")
f.puts str
f.close