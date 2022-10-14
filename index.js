const express = require("express");
const app = express();
const path = require("path");
const fs = require("fs");
const cors = require("cors");

// constants
const DB_PATH = path.resolve("db.json");
const PORT = process.env.PORT || 8000;

// middlewares
app.use(express.json());
app.use(
  cors({
    origin: ["http://localhost:5173", "http://127.0.0.1:5173"],
  })
);
// routes
app.get("/", async (req, res) => {
  fs.readFile(DB_PATH, "utf-8", (err, jsonString) => {
    if (err) return console.log("Error in reading from db");
    let values = JSON.parse(jsonString);
    res.status(200).json({
      totalValues: values.length,
      values,
    });
  });
});

app.post("/", async (req, res) => {
  fs.readFile(DB_PATH, "utf-8", (err, jsonString) => {
    if (err) return console.log("Error in reading from db");
    let body = req.body;
    let valuesArr = JSON.parse(jsonString);
    let img = "";
    if (body.itemname == "Redbull") {
      img = "https://m.media-amazon.com/images/I/51Bp30CR3IL._AC_UL640_QL65_.jpg";
    } else if (body.itemname == "Kellogs Cornflake") {
      img = "https://m.media-amazon.com/images/I/91KZBHX-d-L._AC_UY436_QL65_.jpg";
    } else {
      img = "https://m.media-amazon.com/images/I/71DpoMAG6pL._AC_UL640_QL65_.jpg";
    }

    let obj = {
      price: body.price,
      itemname: body.itemname,
      imgLink: img,
      timestamp: new Date(),
      quantity: 1,
    };

    valuesArr.push(obj);
    console.log(obj);
    fs.writeFile(DB_PATH, JSON.stringify(valuesArr), (err) => {
      if (err) return console.log("Error in updating db");
      res.status(200).json({
        message: "Values saved",
        value: valuesArr[valuesArr.length - 1],
      });
    });
  });
});

app.listen(PORT, () => console.log("Port Started on http://localhost:" + PORT + " 🔥"));
