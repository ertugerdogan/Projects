const http = require('http');
const fs = require('fs');

const server = http.createServer((req, res) => {
  if (req.url === '/getLatestVersionNumber') {
    handleGetLatestVersionNumber(req, res);
  } else if (req.url === '/getLatestSoftware') {
    handleGetLatestSoftware(req, res);
  } else {
    res.statusCode = 200;
    res.setHeader('Content-Type', 'text/html');
    res.end(`GET request for ${req.url}`);
  }
  console.log('\x1b[31m',`Received request from ${req.ip} with status code ${res.statusCode}`);
});

function handleGetLatestVersionNumber(req, res) {
  fs.readFile('version_config.json', (err, data) => {
    if (err) {
      console.error(err);
      res.statusCode = 500;
      res.end();
      return;
    }

    res.statusCode = 200;
    res.setHeader('Content-Type', 'application/json');
    res.end(data);
  });
  console.log('\x1b[32m',`Received request for latest version from ${req.ip} with status code ${res.statusCode}`);
}

function handleGetLatestSoftware(req, res) {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'application/octet-stream');
  fs.createReadStream('latest_software').pipe(res);
  console.log('\x1b[34m',`Received request for latest software from ${req.ip} with status code ${res.statusCode}`);
}

server.listen(8080,()=>{
  console.log('\x1b[7m','Server is alive now.');
});
