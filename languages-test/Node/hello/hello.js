

var http = require('http');
var sayHello = function(request, response)
{
	response.writeHead(200, {'Content-Type': 'text/plane'});
	response.write('hello world');
};

http.createServer(sayHello).listen(8000);