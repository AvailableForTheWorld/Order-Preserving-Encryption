const fs = require("fs");

let readStream = fs.createReadStream("./NE.txt");
let writeStream = fs.createWriteStream("./NE_11.txt");
let buffer = [];

function writeFileWithLine(line, isLastLine) {
  writeStream.write(line);
  if (isLastLine) {
    writeStream.write("\n");
  }
}
readStream.on("readable", () => {
  while ((char = readStream.read(1)) !== null) {
    // if (char[0] === 0x0a) {
    //   writeFileWithLine(Buffer.from(buffer).toString(), false);
    //   buffer.length = 0;
    // } else {
    //   buffer.push(char[0]);
    // }
    console.log(char[0]);
  }
});
readStream.on("end", () => {
  console.log("okk");
  //   writeFileWithLine(Buffer.from(buffer).toString(), true);
});
