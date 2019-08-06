const PORT = 7880;

const express = require('express');
const morgan = require('morgan');
const bodyParser = require('body-parser');
const app = express();

app.use(morgan('dev'));


const log = (req, res, next) => {
  const indent = obj => {
    const text = JSON.stringify(obj, null, 2)
    if (text) {
      return text.split("\n").map(l => `  ${l}`).join("\n");
    }
    return null;
  }
  console.log();
  console.log('  headers', indent(req.headers));
  console.log('  body', indent(req.body));
  res.set('Request-CT', req.header('content-type'));
  next();
};

app.get('/', log, (req, res) => {
  res.send('hello world');
});

app.all('/echo', bodyParser.text({type: '*/*'}), log, (req, res) => {
  res.send(req.body);
});

app.post('/form', bodyParser.urlencoded({extended: false}), log, (req, res) => {
  res.send(req.body.hello);
});

app.post('/json', bodyParser.json(), log, (req, res) => {
  res.json({code: 'SUCCESS', data: req.body});
});

app.listen(PORT, () => console.log(`web server listening on ${PORT}`));
