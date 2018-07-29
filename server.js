const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.json());

app.all('/', (req, res) => {
	res.send('k\n');
	console.log(JSON.stringify(req.body));
});

app.listen(11235);
