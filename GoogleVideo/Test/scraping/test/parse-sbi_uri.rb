

str = '<HTML><HEAD><meta http-equiv="content-type" content="text/html;charset=utf-8">
<TITLE>302 Moved</TITLE></HEAD><BODY>
<H1>302 Moved</H1>
The document has moved
<A HREF="http://www.google.com.br/search?tbs=sbi:AMhZZiufkDNVRv_1tlbiBlkLhsiimUfcXsAc8nPMYvvd05Fa891xvqNZ-NzSn9BiWlZfXlpjcRg4JAY8ZAq_1YOth_1DZnUtrEUKJdlmcn_1maoMub6hL_1NmXx8TusaqVhzATEk3NO_1FnJnXmdLB1FMzUQD3YmCP1E1uqroYyZAKKMGbjlqikLKG971UeUvk6KJ2YJ6eLjzy91VIwgplAw-O_1_1Qys7VfXLdQG23Qo1xlGiCnraHAw5dW_1AIje6JnZgEPiyJ0olXhtauAtQWeickYFBYKbfjS55HI9fmgLnJpI6fNXLrCoVVltZE4Rppa51viq-9WllPRQ-JX0Hvi8ihTvYcWxS9J2_1vk3SXathRHM7orkHICqxwxzbwo9uJ7_1wx_1Ns7AEF6E-SqjrIKk3Tr-MquHpYpjXeeV93iaiUjDwfbJ-4xP5UFtKw29r3dOpfBupT9aTaDW_1IUYk9gsehqwDhuk2ppXnMgVTC2-2VPFtA-Af9b4tK6UhVGdi2YJmzW2FxWYpe0ABuwAOHOvN_15Q9NflvwGAkhvelHgWry8Guy5spKYlVXHjpwnodmcV2HR6VCDdWDefvPF5Lq8l5h_103J-Hb3yzxXeG8BgLR7TV_1pdcxD7pGHTApJkwITuLnJnr1iKVkdLDrlaOHTKmqb2s0OseKdZf9qvcu06DJIpLt-k9Qi8TUmv46ZjKhPh3wZOJ_1S7XQMi2KAnFhZymvxnTB8I95hk_1JHI7XvyGU0BDSwZj8qA388h-AY7_1ZQMwfv_1EPYeHcBP6z9EmI5rKgMEV0QrPdUQ5ebhCJ3zCeCd7UoPg-vl82BYmWgPVYGHdGt4HbErlE0ou1SwPyISnmTU64az4bZNdVdeBGDOYJD9gCqJhC60Z3dYhIN4qq8xvAqPnC23XHo3N8ZJDQlGwOTQAhQBPSlvVAFot4B8eS8_1Dsio407puttcNTRH_1OcA9GeoOotS6Gl1ss-HJt314D20cgdcOY8XXoDp0WnZc254u2KPXdtyH-NMkAT4Wb7j28mGhEpHklT2NGlAhmWlUpORJ9DSUtxNwLodtoaAcXHYP99spZBJmN-13jdIVBuyBffB2PSsEEe0P9ZpBeqTzK-O7WBsPngaf1JATo5yekEQhdMT1k7RN8JBgv8d9WQbq6R7VJ_14bJxHMTvzI">here</A>. 
</BODY></HTML> '

if /HREF="(.+?)"/ =~ str
  
  ua = '"Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_4) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.94 Safari/537.4"'
  url = $1
  
  response = `curl -L -A #{ua} #{$1}`
  
end

  
