const express = require("express");
const fs = require("fs");
const cors = require("cors");
const exec = require("child_process").execFile;
const morgan = require("morgan");

const app = express();

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.set("port", process.env.PORT || 8001);
if (process.env.NODE_ENV === "production") {
  app.use(morgan("combined"));
} else {
  app.use(morgan("dev"));
}

//input fileName and req.body data will make res to client
const makeResponse = async (fileName, data, res) => {
  await fs.writeFile(`${fileName}.in`, data, (err) => {
    console.log(`${fileName}.in file is created`);
    exec(`${fileName}.exe`, () => {
      console.log(`${fileName}.exe is excecuted`);
      fs.readFile(`${fileName}.out`, (err, data) => {
        const output = data.toString();
        console.log(output);
        res.json({ data: output });
      });
    });
  });
};

const makeBotResponse = async (bot, data, res) => {
  await fs.writeFile(`bot.in`, data, (err) => {
    console.log(`bot.in file is created`);
    exec(`${bot}.exe`, () => {
      console.log(`${bot}.exe is excecuted`);
      fs.readFile(`bot.out`, (err, data) => {
        let output = data.toString();
        output = output.replace(/\s/g, "");
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
      makeResponse("panduan", data, res);
    });
  } else {
    makeResponse("panduan", data, res);
  }
});

// send back output
app.post("/shengfu", async (req, res) => {
  const { data } = req.body;
  console.log(data);
  if (fs.existsSync("shengfu.in")) {
    //if file exist, delete first
    fs.unlink("shengfu.in", () => {
      makeResponse("shengfu", data, res);
    });
  } else {
    makeResponse("shengfu", data, res);
  }
});

app.post("/bot", async (req, res) => {
  const { data, bot } = req.body;
  if (fs.existsSync("bot.in")) {
    //if file exist, delete first
    fs.unlink("bot.in", () => {
      makeBotResponse(bot, data, res);
    });
  } else {
    makeBotResponse(bot, data, res);
  }
});

app.post("/test", async (req, res) => {
  res.json({ data: "Hello" });
});

app.listen(app.get("port"), () => {
  console.log(app.get("port"), "번 포트에서 대기 중");
});
