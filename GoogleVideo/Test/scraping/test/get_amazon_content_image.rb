# -*- encoding: Shift_JIS -*-
require 'rubygems'
require	'mechanize'

agent = Mechanize.new
agent.keep_alive = false
agent.max_history = 1
agent.open_timeout = 60
agent.read_timeout = 180

targetASIN = "4774158968" # ASINコード
targetURI = "http://amazon.jp/dp/" + targetASIN.chomp # URLの編集
puts targetURI

agent.get(targetURI) #webPageの取得

puts agent.page.search('title').inner_text # タイトル

src = agent.page.search('//*[@id="prodImage"]').at('img')['src'] # 商品画像
puts src
agent.get(src).save_as("./img/" + targetASIN.chomp + ".jpg") # 保存する