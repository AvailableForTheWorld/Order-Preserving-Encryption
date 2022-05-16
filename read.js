const fs = require("fs");
const readline = require("readline");

const r = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

r.on("line", (input) => {
  const inputArr = input.split(" ");
  const rl = readline.createInterface({
    input: fs.createReadStream("./NE.txt"),
  });
  const crypto = (n) =>
    Math.floor(
      n * inputArr[0] * 1000000 +
        Number(inputArr[1]) +
        Math.random() * (inputArr[0] - 1)
    );
  rl.on("line", (line) => {
    const arr = line.split(" ");
    console.log(crypto(arr[0]), crypto(arr[1]));
  });
  r.close();
});
