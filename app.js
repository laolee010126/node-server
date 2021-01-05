const express = require("express");
const fs = require("fs");
const cors = require("cors");

const app = express();

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: false }));

app.post("/panduan", async (req, res) => {
  const { data } = req.body;
  await fs.writeFile("panduan.in", data, (err) => {
    console.log("haha");
  });
  fs.open("panduan.exe", () => {
    console.log("exp file opned");
  });
});

app.post("/shengfu", async (req, res) => {
  const { query } = await req.body;
});

app.listen(3000, () => {
  console.log("server is running on port: 3000");
});
