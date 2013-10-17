
result = []

f = open("res.html")
f.each { |line|
  
  # p line
  result << line.scan(/imgurl=(http.+?)&amp/)
}
f.close