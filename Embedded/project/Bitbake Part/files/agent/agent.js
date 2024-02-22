const http = require('http');
const https = require('https');
const fs = require('fs');

function getLatestSoftwareVersionNumber() {
  return new Promise((resolve, reject) => {
    https.get('http://192.168.1.102:8080/getLatestVersionNumber', (res) => {
      let data = '';

      res.on('data', (chunk) => {
        data += chunk;
      });

      res.on('end', () => {
        try {
          const parsedData = JSON.parse(data);
          resolve(parsedData.latestVersion);
        } catch (e) {
          reject(e);
        }
      });
    }).on('error', (e) => {
      reject(e);
    });
  });
}

function getLatestSoftware() {
  return new Promise((resolve, reject) => {
    https.get('http://192.168.1.102:8080/getLatestSoftware', (res) => {
      const file = fs.createWriteStream('latest_software');
      res.pipe(file);
      file.on('finish', () => {
        file.close();
        resolve();
      });
    }).on('error', (e) => {
      reject(e);
    });
  });
}

function readCurrentVersion() {
  return new Promise((resolve, reject) => {
    fs.readFile('software_info.json', (err, data) => {
      if (err) {
        reject(err);
      } else {
        try {
          const parsedData = JSON.parse(data);
          resolve(parsedData.currentVersion);
        } catch (e) {
          reject(e);
        }
      }
    });
  });
}

(async () => {
  try {
    const latestVersion = await getLatestSoftwareVersionNumber();
    const currentVersion = await readCurrentVersion();
    if (latestVersion > currentVersion) {
      await getLatestSoftware();
    }
  } catch (e) {
    console.error(e);
  }
})();
