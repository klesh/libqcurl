const PORT = 7880;

const express = require('express');
const morgan = require('morgan');
const bodyParser = require('body-parser');
const app = express();

app.use(morgan('dev'));

app.get('/', (req, res) => {
  res.send('hello world');
});

app.all('/echo', bodyParser.text({type: '*/*'}), (req, res) => {
  console.log('headers', req.headers);
  console.log('body', req.body);
  res.send(req.body);
});

app.post('/form', bodyParser.urlencoded({extended: false}), (req, res) => {
  res.send(req.body.hello);
});

app.listen(PORT, () => console.log(`web server listening on ${PORT}`));
