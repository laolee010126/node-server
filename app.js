const express = require("express");
const fs = require("fs");
const cors = require("cors");
const exec = require("child_process").execFile;

const app = express();

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

//input fileName and req.body data will make res to client
const makeResponse = async (fileName, data) => {
  await fs.writeFile(`${fileName}.in`, data, (err) => {
    console.log(`${fileName}.in file is created`);
    exec(`${fileName}.exe`, () => {
      console.log(`${fileName}.exe is excecuted`);
      fs.readFile(`${fileName}.out`, (err, data) => {
        const output = data.toString();
        res.json({ data: output });
      });
    });
  });
};

// send back output
app.post("/panduan", async (req, res) => {
  const { data } = req.body;
  if (fs.existsSync("panduan.in")) {
    //if file exist, delete first
    fs.unlink("panduan.in", () => {
      makeResponse("panduan", data);
    });
  } else {
    makeResponse("panduan", data);
  }
});

// send back output
app.post("/shengfu", async (req, res) => {
  const { data } = req.body;
  if (fs.existsSync("shengfu.in")) {
    //if file exist, delete first
    fs.unlink("shengfu.in", () => {
      makeResponse("shengfu", data);
    });
  } else {
    makeResponse("shengfu", data);
  }
});

app.listen(3000, () => {
  console.log("server is running on port: 3000");
});
